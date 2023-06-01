#include "computorv2.h"

static int	ft_validate_add_sub(char op, t_list **stack_vars, t_list **stack_op)
{
	t_var	o;
	int		ret;
	double	num;

	if (!stack_vars || !stack_op)
		return (-1);
	ret = ft_stack_top(*stack_op, &o);
	if (ret == -1)
		return (-1);
	num = 1;
	if (op == '-')
		num = -1;
	if (!ret || o.choice.ch == '(')
	{
		if (ft_parse_num_str(0, num, stack_vars) == -1)
			return (-1);
		return (ft_process_stack_add(stack_vars, stack_op, '*'));
	}
	return (ft_process_stack_add(stack_vars, stack_op, op));
}

static int	ft_validate_op(char **inp, t_list **stack_vars, t_list **stack_op)
{
	int		ret;
	char	op;

	if (!inp || !stack_vars || !stack_op)
		return (-1);
	op = *((*inp)++);
	ret = ft_valid(op);
	if (ret != 3 || ret != 4 || ret != 5)
		return (-1);
	if (ret == 5 && *((*inp)) == '*')
	{
		(*inp) += 1;
		return (ft_process_stack_add(stack_vars, stack_op, 'm'));
	}
	if (ret == 5)
		return (ft_process_stack_add(stack_vars, stack_op, '*'));
	return (ft_validate_add_sub(op, stack_vars, stack_op));
}

static int	ft_validate_inp(char **inp, t_list *vars,
				t_list **stack_vars, t_list **stack_op)
{
	int		ret;

	if (!inp || !stack_vars || !stack_op)
		return (-1);
	ret = ft_valid(*(*inp));
	if (ret == 2)
		return (ft_parse_num_str(inp, 0, stack_vars));
	if (ret == 1)
		return (ft_parse_var(inp, vars, stack_vars));
	if (ret == 6 || ret == 8 || ret == 9 || ret == 10)
		return (ft_process_stack_add(stack_vars, stack_op, *((*inp)++)));
	return (ft_validate_op(inp, stack_vars, stack_op));
}

static int	ft_empty_stacks(t_list **stack_vars, t_list **stack_op, t_var *new_v)
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
	t_list		*stack_vars;
	t_list		*stack_op;
	int			ret;

	if (!inp || !new_v)
		return (-1);
	stack_vars = 0;
	stack_op = 0;
	ret = 0;
	while (ret > -1 && (*(*inp) || (*(*inp)) == '='))
	{
		ret = ft_parse_inp_move(inp);
		if (ret == 7)
			continue ;
		ret = ft_validate_inp(inp, vars, &stack_vars, &stack_op);
	}
	ret = ft_empty_stacks(&stack_vars, &stack_op, new_v);
	ft_stack_free(&stack_vars);
	ft_stack_free(&stack_op);
	return (ret);
}
