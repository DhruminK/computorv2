/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:51:57 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:59:04 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_var_poly_init(t_var *v, t_var_type type, int8_t degree, char *var_name)
{
	if (!v)
		return (-1);
	memset(v, 0, sizeof(t_var));
	if (var_name)
		v->var_name = strdup(var_name);
	v->type = type;
	if (type == CV2_POLY || type == CV2_COMPLEX
		|| type == CV2_RATIONAL || type == CV2_COMPLEX)
		return (ft_poly_init(&(v->choice.poly), degree, 0));
	return (0);
}
