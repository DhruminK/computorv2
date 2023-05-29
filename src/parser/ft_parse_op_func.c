#include "computorv2.h"

int	ft_perform_stack_empty(t_list **stack_vars, t_list **stack_op, uint8_t cbrac)
{
	int		ret;
	t_stack	s;

	if (!stack_vars || !stack_op)
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		if (ft_stack_op(*stack_op, &s) < 1)
			return (-1);
		ret = ft_perform_stack_op(stack_vars, stack_op, 0, 1);
		if (ret < 1)
			continue ;
		if (cbrac && s.vars.ch == '(')
			ret = 0;
	}
	return (ret);
}

int	ft_perform_stack_push(t_list **stack_vars, t_list **stack_op, char op)
{
	int		ret;

	if (!stack_vars || !stack_op)
		return (-1);
	ret = 1;
	while (ret > 0)
		ret = ft_perform_stack_op(stack_vars, stack_op, op, 0);
	if (ret < 0)
		return (-1);
	if (ft_stack_push(stack_op, STACK_OP, (void *)&op) == -1)
		return (-1);
	return (0);
}

int	ft_parse_op(char **inp, t_list **stack_vars, t_list **stack_op)
{
	char	ch;

	if (!inp || !stack_vars || !stack_op)
		return (-1);
	ch = *(*inp);
	(*inp) += 1;
	if (ch == ')')
		return (ft_perform_stack_empty(stack_vars, stack_op, 1));
	return (ft_perform_stack_push(stack_vars, stack_op, ch));
}
