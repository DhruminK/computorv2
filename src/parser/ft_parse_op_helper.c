#include "computorv2.h"

static int	ft_perofrm_operation(t_poly *out, t_poly *p1, t_poly *p2, char op)
{
	int	ret;

	ret = 0;
	if (op == '+')
		ret = ft_poly_add(out, p1, p2);
	else if (op == '-')
		ret = ft_poly_sub(out, p1, p2);
	else if (op == '*')
		ret = ft_poly_mult(out, p1, p2);
	else if (op == '/')
		ret = ft_poly_div(out, p1, p2);
	else if (op == '^')
		ret = f1_poly_pow(out, p1, p2);
	else
		return (-1);
	return (ret);
}

static int	ft_perform_var_op(t_list **stack_vars, char op)
{
	t_stack	*v1;
	t_stack	*v2;
	t_poly	*poly;
	int		ret;

	if (!stack_vars)
		return (-1);
	if (ft_stack_pop(stack_vars, &v2) < 1
			|| ft_stack_pop(stack_vars, &v1) < 1)
		return (-1);
	poly = malloc(sizeof(t_poly));
	ret = ft_perform_operation(poly, v1.vars.poly, v2.vars.poly, op);
	ft_poly_free(v1.vars.poly);
	free(v1.vars.poly);
	ft_poly_free(v2.vars.poly);
	free(v2.vars.poly);
	if (ret != -1 && ft_stack_push(stack_vars, STACK_NUM, (void *)poly) != -1)
		return (0);
	free(poly);
	return (-1);
}

static int	ft_op_precedence(char op)
{
	if (ch == '+' || ch == '-')
		return (1);
	else if (ch == '*' || ch == '/')
		return (2);
	else if (ch == '^')
		return (3);
	return (0);
}

int	ft_perform_stack_op(t_list **stack_vars, t_list **stack_op, char op, int is_empty)
{
	t_stack	s;
	t_stack	*op_s;
	int		ret;

	if (!stack_var || !stack_op)
		return (-1);
	if (!*stack_op)
		return (0);
	ft_stack_top(*stack_op, &s);
	if (!is_empty && ft_op_precedence(s.vars.ch) <= ft_op_precedence(op))
		return (0);
	if (ft_stack_pop(stack_op, &op_s) == -1)
		return (-1);
	if (op_s->vars.ch != '(')
		ret = ft_perform_var_op(stack_vars, op_s->vars.ch);
	memset(op_s, 0, sizeof(t_stack));
	free(op_s);
	if (ret == -1)
		return (ret);
	return (1);
}
