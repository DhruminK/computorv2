#include "computorv2.h"

static int	ft_process_stack_free(t_var *v1, t_var *v2, t_var *op, t_poly_op *poly_op)
{
	t_var	new_v;
	int		ret;

	ret = -1;
	if (v1 && v2 && op && poly_op)
	{
		ret = 0;
		if (ft_var_op(&new_v, v1, v2, op->choice.ch) == -1)
			ret = -1;
		if (!ret && ft_stack_push(&(poly_op->stack_vars), &new_v) == -1)
			ret = -1;
	}
	ft_var_free(op);
	ft_var_free(v1);
	ft_var_free(v2);
	if (v1)
		free(v1);
	if (v2)
		free(v2);
	if (op)
		free(op);
	return (ret);
}

int	ft_process_stack_op(t_poly_op *poly_op)
{
	t_var	*op;
	t_var	*v1;
	t_var	*v2;

	if (!poly_op)
		return (-1);
	op = 0;
	v1 = 0;
	v2 = 0;
	ft_stack_pop(&(poly_op->stack_op), &op);
	if (op && op->choice.ch == '(')
	{
		ft_process_stack_free(v1, v2, op, poly_op);
		return (1);
	}
	ft_stack_pop(&(poly_op->stack_vars), &v1);
	ft_stack_pop(&(poly_op->stack_vars), &v2);
	return (ft_process_stack_free(v1, v2, op, poly_op));
}

int	ft_empty_op_stack(t_poly_op *poly_op, uint8_t cbrac)
{
	int	ret;

	if (!poly_op)
		return (-1);
	while (poly_op->stack_op)
	{
		ret = ft_process_stack_op(poly_op);
		if (ret == 1 && cbrac)
			return (0);
		if (ret == -1)
			return (-1);
	}
	if (cbrac)
		return (-1);
	return (0);
}

int	ft_add_op_stack(t_poly_op *poly_op, char op)
{
	int		op_prece1;
	int		ret;
	t_var	v;
	t_var	new_v;

	if (!poly_op)
		return (-1);
	new_v.type = CV2_OP;
	new_v.choice.ch = op;
	if (op == ')')
		return (ft_empty_op_stack(poly_op, 1));
	op_prece1 = ft_op_precedence(op);
	ret = 0;
	while (ret == -1 && op != '(' && poly_op->stack_op)
	{
		ft_stack_top(poly_op->stack_op, &v);
		if (ft_op_precedence(v.choice.ch) < op_prece1)
			ret = ft_process_stack_op(poly_op);
		else
			break ;
	}
	poly_op->prev_type = CV2_OP;
	new_v.var_name = 0;
	if (ret == 0 && ft_stack_push(&(poly_op->stack_op), &new_v) == -1)
		return (-1);
	return (ret);
}

int	ft_parse_op(char **inp, t_poly_op *poly_op)
{
	int		ret;
	char	op;

	if (!inp || !poly_op)
		return (-1);
	op = *(*inp);
	ret = ft_parse_op_validate(op, poly_op);
	if (ret != 0)
		return (ret);
	ret = ft_valid(*((*inp)++));
	if (ret == 1 || ret == 2 || ret == 7)
		return (-1);
	if (ret == 5 && *(*inp) == '*')
	{
		(*inp) += 1;
		op = 'm';
	}
	return (ft_add_op_stack(poly_op, op));
}
