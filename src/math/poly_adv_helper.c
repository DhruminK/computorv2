/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_adv_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:55:17 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/08 15:13:00 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2)
{
	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 0 || p2->degree != 0)
		return (-1);
	out->degree = 0;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	if (ft_cd_div(out->coff, p1->coff[0], p2->coff[0]) == -1)
		return (-1);
	return (0);
}

static int	ft_complex_poly_pow(t_cd *cd, t_poly *p1, t_poly *p2)
{
	double	frac;

	if (!cd || !p1 || !p2)
		return (-1);
	frac = p2->coff->real;
	frac = frac - (long)frac;
	if (frac != 0.0)
		return (-1);
	if (ft_cd_pow(cd, p1->coff[0], (int)(p2->coff->real)) == -1)
		return (-1);
	return (0);
}

int	ft_poly_pow(t_poly *out, t_poly *p1, t_poly *p2)
{
	t_cd	c;

	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 0.0 || p2->degree != 0.0 || p2->coff->imag != 0.0)
		return (-1);
	out->degree = 0;
	c.real = 0.0;
	c.imag = 0.0;
	if (p1->coff->imag != 0.0 && ft_complex_poly_pow(&c, p1, p2) == -1)
		return (-1);
	else if (p1->coff->imag == 0.0 && ft_gen_pow(p1->coff->real,
			p2->coff->real, &(c.real)) == -1)
		return (-1);
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	memcpy(out->coff, &c, sizeof(t_cd));
	return (0);
}
