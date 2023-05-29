/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_adv_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:55:17 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 14:56:14 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2)
{
	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 1 || p2->degree != 1)
		return (-1);
	out->degree = 0;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	if (ft_cd_div(out->coff, p1->coff[0], p2->coff[0]) == -1)
		return (-1);
	return (0);
}

int	ft_poly_pow(t_poly *out, t_poly *p1, t_poly *p2)
{
	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 1 || p2->degree != 1
		|| p2->coff[0] - (int)p2->coff[0] != 0.0)
		return (-1);
	out->degree = 0;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	if (ft_cd_pow(out->coff, p1->coff[0], (int)(p2->coff[0])) == -1)
		return (-1);
	return (0);
}
