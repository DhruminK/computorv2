/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:25:17 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 12:25:18 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_process_func_op(t_var *out, t_var *func, t_var *arg)
{
	if (!func || !arg)
		return (-1);
	if (arg->type == CV2_RATIONAL)
		return (ft_func_num_process(out, func, arg));
	if (arg->type == CV2_POLY || arg->type == CV2_FUNC)
		return (ft_func_poly_process(out, func, arg));
	return (-1);
}
