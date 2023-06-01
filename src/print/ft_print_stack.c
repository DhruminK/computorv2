/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:54:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 16:59:35 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_stack_print(t_list *stack)
{
	t_var	*v;

	while (stack)
	{
		v = (t_var *)(stack->content);
		ft_print_var(v);
		stack = stack->next;
	}
}
