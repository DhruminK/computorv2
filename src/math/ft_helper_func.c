/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:43:53 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/22 16:45:13 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_cd_scalar_mult(t_cd *out, double num, t_cd c)
{
	if (!out)
		return (-1);
	out->real = num * c.real;
	out->imag = num * c.imag;
	return (0);
}
