#include "computorv2.h"

static int	ft_push_num_stack(char **inp, int val,
				t_list **stack_vars, t_list *vars)
{
	t_poly	*poly;
	int		ret;

	poly = malloc(sizeof(t_poly));
	if (!poly)
		return (-1);
	ret = 0;
	if (val == 2 && ft_poly_init(poly, 0, 0) == -1)
		ret = -1;
	if (val == 2)
		ft_parse_num(inp, poly->coff, 0);
	if (val == 1 && ft_parse_var(inp, vars, poly) == -1)
		ret = -1;
	if (ret != -1 && ft_stack_push(stack_vars, STACK_NUM, poly) == 0)
		return (0);
	ft_poly_free(poly);
	if (poly)
		free(poly);
	return (-1);
}

static int	ft_parse_safe_exit(t_poly **poly, t_list **stack_vars,
				t_list **stack_op)
{
	int		ret;
	int		var_len;
	int		op_len;

	if (!poly || !stack_vars || !stack_op)
		return (-1);
	ret = 0;
	if (ft_perform_stack_empty(stack_vars, stack_op, 0) == -1)
		ret = -1;
	var_len = ft_stack_len(*stack_vars);
	op_len = ft_stack_len(*stack_op);
	if (ret != -1 && var_len == 1 && op_len == 0)
	{
		*poly = ((t_stack *)(*stack_var)->content)->vars.poly;
		((t_stack *)(*stack_var)->content)->vars.poly = 0;
	}
	else
		ret = -1;
	ft_free_stack(stack_vars);
	ft_free_stack(stack_op);
	return (ret);
}

int	ft_parse_poly(char **inp, t_poly **poly, t_list *vars)
{
	t_list	*stack_vars;
	t_list	*stack_op;
	int		ret;

	if (!inp || !poly || !vars)
		return (-1);
	stack_vars = 0;
	stack_op = 0;
	while (*(*inp) && *(*inp) != '=')
	{
		ret = ft_parse_inp_move(inp);
		if (ret == 7)
			break ;
		if (ret == 1 || ret == 2)
			ret = ft_push_num_stack(inp, ret, &stack_vars, vars);
		else
			ret = ft_push_op(inp, stack_vars, stack_op);
		if (ret < 0)
			break ;
	}
	return (ft_parse_safe_exit(poly, stack_vars, stack_op));
}
