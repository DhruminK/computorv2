/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:59:15 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:58:37 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_cd_init(t_cd *out, double real, double imag)
{
	if (!out)
		return ;
	out->real = real;
	out->imag = imag;
}

int	ft_cd_add(t_cd *out, t_cd c1, t_cd c2, uint8_t sub)
{
	if (!out)
		return (-1);
	if (sub == 0)
	{
		out->real = c1.real + c2.real;
		out->imag = c1.imag + c2.imag;
	}
	else
	{
		out->real = c1.real - c2.real;
		out->imag = c1.imag - c2.imag;
	}
	return (0);
}

int	ft_cd_mult(t_cd *out, t_cd c1, t_cd c2)
{
	if (!out)
		return (-1);
	out->real = (c1.real * c2.real) - (c1.imag * c2.imag);
	out->imag = (c1.real * c2.imag) + (c1.imag * c2.real);
	return (0);
}

int	ft_cd_div(t_cd *out, t_cd c1, t_cd c2)
{
	t_cd	c;
	double	abs;

	abs = (c2.real * c2.real) + (c2.imag * c2.imag);
	if (!out || !abs)
		return (-1);
	c.real = c2.real / abs;
	c.imag = -1 * c2.imag / abs;
	*out = ft_cd_mult(c1, c);
	return (0);
}

int	ft_cd_pow(t_cd *out, t_cd c, int pow)
{
	int	i;
	int	div;

	if (!out)
		return (-1);
	out.real = 1.0;
	out.imag = 0.0;
	if (pow == 0)
		return (0);
	div = 1;
	if (pow < 0)
		div = -1;
	i = 0;
	while (i != pow)
	{
		if (pow > 0)
			ft_cd_mult(out, *out, c);
		else
			ft_cd_div(out, *out, c);
		i += div;
	}
	return (0);
}
