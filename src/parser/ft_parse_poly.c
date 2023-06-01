/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_poly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:20:50 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 18:39:09 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_validate_add_sub(char op, t_poly_op *poly_op,
				t_var_type prev_type)
{
	t_var	top;
	double	num;
	int		ret;

	if (!poly_op)
		return (-1);
	num = (-2) * (ft_valid(op) - 3.5);
	ret = ft_stack_top(poly_op->stack_op, &top);
	if (ret == -1)
		return (-1);
	if (!(poly_op->stack_vars) || (ret && top.choice.ch != op
			&& prev_type == CV2_OP))
	{
		if (ft_process_stack_add(&(poly_op->stack_vars),
				&(poly_op->stack_op), '*') == -1)
			return (-1);
		return (ft_parse_num_str(0, num, &(poly_op->stack_vars)));
	}
	return (ft_process_stack_add(&(poly_op->stack_vars),
			&(poly_op->stack_op), op));
}

static int	ft_validate_op(char **inp, t_poly_op *poly_op, t_var_type prev_type)
{
	int		ret;
	char	op;

	if (!inp || !poly_op)
		return (-1);
	op = *((*inp)++);
	ret = ft_valid(op);
	if (ret != 3 && ret != 4 && ret != 5)
		return (-1);
	if (ret == 5 && *(*inp) == '*')
	{
		(*inp) += 1;
		return (ft_process_stack_add(&(poly_op->stack_vars),
				&(poly_op->stack_op), 'm'));
	}
	if (ret == 5)
		return (ft_process_stack_add(&(poly_op->stack_vars),
				&(poly_op->stack_op), '*'));
	return (ft_validate_add_sub(op, poly_op, prev_type));
}

static int	ft_validate_inp(char **inp, t_list *vars, t_poly_op *op)
{
	int			ret;
	t_var_type	prev_type;

	if (!inp || !op)
		return (-1);
	ret = ft_valid(*(*inp));
	prev_type = op->prev_type;
	op->prev_type = CV2_OP;
	if (ret == 2 || ret == 1)
		op->prev_type = CV2_RATIONAL;
	if (ret == 2)
		return (ft_parse_num_str(inp, 0, &(op->stack_vars)));
	if (ret == 1)
		return (ft_parse_var(inp, vars, &(op->stack_vars)));
	if (ret == 6 || ret == 8 || ret == 9 || ret == 10)
		return (ft_process_stack_add(&(op->stack_vars),
				&(op->stack_op), *((*inp)++)));
	return (ft_validate_op(inp, op, prev_type));
}

static int	ft_empty_stacks(t_list **stack_vars,
				t_list **stack_op, t_var *new_v)
{
	t_var	*v;

	if (!stack_vars || !stack_op || !new_v)
		return (-1);
	memset(new_v, 0, sizeof(t_var));
	if (ft_process_stack(stack_vars, stack_op, 0) == -1)
		return (-1);
	if (ft_stack_pop(stack_vars, &v) < 1)
		return (-1);
	memcpy(new_v, v, sizeof(t_var));
	free(v);
	if (*stack_vars || *stack_op)
		return (-1);
	return (0);
}

int	ft_parse_poly(char **inp, t_list *vars, t_var *new_v)
{
	t_poly_op	op;
	int			ret;

	if (!inp || !new_v)
		return (-1);
	memset(&op, 0, sizeof(t_poly_op));
	ret = 0;
	while (ret > -1 && (*(*inp)) && (*(*inp) != '='))
	{
		ret = ft_parse_inp_move(inp);
		if (ret == 7)
			continue ;
		ret = ft_validate_inp(inp, vars, &op);
	}
	ret = ft_empty_stacks(&(op.stack_vars), &(op.stack_op), new_v);
	ft_stack_free(&(op.stack_vars));
	ft_stack_free(&(op.stack_op));
	return (ret);
}
