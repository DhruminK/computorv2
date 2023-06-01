/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:31:03 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 15:36:59 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_stack_push(t_list **stack, t_var *var)
{
	t_list	*ele;

	if (!stack || !var)
		return (-1);
	ele = ft_lstnew(var, sizeof(t_var));
	if (!ele)
		return (-1);
	ft_lstadd_front(stack, ele);
	return (0);
}

int	ft_stack_pop(t_list **stack, t_var **var)
{
	t_list	*ele;

	if (!stack || !var)
		return (-1);
	if (!*stack)
		return (0);
	ele = (*stack);
	(*stack) = (*stack)->next;
	*var = (t_var *)(ele->content);
	free(ele);
	ele = 0;
	return (1);
}

int	ft_stack_top(t_list *stack, t_var *var)
{
	if (!var)
		return (-1);
	if (!stack)
		return (0);
	memcpy(var, stack->content, sizeof(t_var));
	return (1);
}

int	ft_stack_len(t_list *stack)
{
	int	len;

	len = 0;
	while (stack)
	{
		len += 1;
		stack = stack->next;
	}
	return (len);
}

void	ft_stack_free(t_list **stack)
{
	t_var	*var;
	int		ret;

	if (!stack)
		return ;
	ret = 1;
	var = 0;
	while (ret > 0)
	{
		ret = ft_stack_pop(stack, &var);
		if (ret < 1)
			break ;
		ft_var_free(var);
		free(var);
		var = 0;
	}
}
