/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_frac.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:10 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/06 15:38:40 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static void	ft_extract_frac(double num, long *numr, long *deno)
{
	double	frac;
	long	int_part;

	frac = num - (long)num;
	*deno = 1;
	*numr = 0;
	while (frac != 0.0)
	{
		frac *= 10;
		*deno *= 10;
		int_part = (long)(frac - (frac - (long)frac));
		*numr = (*numr * 10) + int_part;
		frac = frac - (long)frac;
	}
	int_part = (long)(num - (num - (long)num));
	*numr = (int_part * (*deno)) + *numr;
}

static void	ft_eliminate_factors(long *numr, long *deno)
{
	long	factor;

	if (*deno == 1 && *numr == 1)
		return ;
	if (*numr == *deno)
	{
		*numr = 1;
		*deno = 1;
		return ;
	}
	factor = 0;
	while (factor != 1)
	{
		factor = ft_gcd(*deno, *numr);
		*numr /= factor;
		*deno /= factor;
	}
}

void	ft_gen_frac(double num, long *numr, long *deno)
{
	int8_t	is_minus;

	if (!numr || !deno)
		return ;
	*numr = 0;
	*deno = 1;
	is_minus = 1;
	if (num == 0.0)
		return ;
	if (num < 0.0)
		is_minus = -1;
	ft_extract_frac(num * is_minus, numr, deno);
	ft_eliminate_factors(numr, deno);
	if (is_minus == -1)
		(*numr) *= -1;
}
