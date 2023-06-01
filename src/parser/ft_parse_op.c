/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:06:13 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 19:11:13 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_free_stack_vars(t_var **v1, t_var **v2, t_var **op, int ret)
{
	t_var	*v;

	if (!v1 || !v2 || !op)
		return (-1);
	v = *v1;
	ft_var_free(v);
	if (*v1)
		free(*v1);
	v = *v2;
	ft_var_free(v);
	if (*v2)
		free(*v2);
	v = *op;
	ft_var_free(v);
	if (*op)
		free(*op);
	return (ret);
}

static int	ft_process_stack_op(t_list **stack_vars, t_list **stack_op)
{
	t_var	*v1;
	t_var	*v2;
	t_var	v;
	t_var	*op;
	int		ret;

	if (!stack_vars || !stack_op)
		return (-1);
	ret = ft_stack_pop(stack_op, &op);
	if (ret > 0)
		ret = ft_stack_pop(stack_vars, &v1);
	if (ret > 0)
		ret = ft_stack_pop(stack_vars, &v2);
	if (ret > 0 && ft_var_op(&v, v1, v2, op->choice.ch) == -1)
		ret = -1;
	if (ret > 0 && ft_stack_push(stack_vars, &v) == -1)
		ret = -1;
	if (ret == 0)
		ret = -1;
	return (ft_free_stack_vars(&v1, &v2, &op, ret));
}

int	ft_process_stack(t_list **stack_vars, t_list **stack_op, uint8_t cbrac)
{
	t_var	v;
	t_var	*op;

	if (!stack_vars || !stack_op)
		return (-1);
	while (*stack_op)
	{
		ft_stack_top(*stack_op, &v);
		if (v.choice.ch == '(')
		{
			if (ft_stack_pop(stack_op, &op) < 0)
				return (-1);
			if (cbrac)
				return (0);
			continue ;
		}
		if (ft_process_stack_op(stack_vars, stack_op) == -1)
			return (-1);
	}
	if (cbrac)
		return (-1);
	return (0);
}

int	ft_process_stack_add(t_list **stack_vars, t_list **stack_op, char op)
{
	t_var	v;
	int		pr_op;
	int		pr;

	if (!stack_vars || !stack_op)
		return (-1);
	if (op == ')')
		return (ft_process_stack(stack_vars, stack_op, 1));
	pr_op = ft_op_precedence(op);
	while (*stack_op && op != '(')
	{
		ft_stack_top(*stack_op, &v);
		pr = ft_op_precedence(v.choice.ch);
		if (pr <= pr_op)
			break ;
		if (ft_process_stack_op(stack_vars, stack_op) == -1)
			return (-1);
	}
	memset(&v, 0, sizeof(v));
	v.type = CV2_OP;
	v.choice.ch = op;
	if (ft_stack_push(stack_op, &v) == -1)
		return (-1);
	return (0);
}
