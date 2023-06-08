/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:35:21 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/08 15:17:34 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_newton(double val, uint16_t pow, double *out)
{
	double	f;
	double	fp;
	double	xn;
	int8_t	i;

	if (!out || val < 0.0)
		return (-1);
	if (pow == 1)
		return (val);
	xn = val;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		f = ft_pow(xn, pow) - val;
		fp = pow * (ft_pow(xn, pow - 1));
		xn = xn - (f / fp);
	}
	*out = xn;
	return (0);
}

int	ft_gen_pow(double val, double pow, double *out)
{
	long	numr;
	long	deno;
	double	root;

	if (!out)
		return (-1);
	ft_gen_frac(pow, &numr, &deno);
	*out = ft_pow(val, numr);
	if (deno > 1 && numr < 0)
		return (-1);
	if (deno > 1 && ft_newton(val, (uint16_t)deno, &root) == -1)
		return (-1);
	if (numr != 1 && deno > 1)
		*out = *out * root;
	else if (deno > 1)
		*out = root;
	return (0);
}
