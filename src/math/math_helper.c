/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:13:19 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/06 14:26:24 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

double	ft_pow(double val, int n)
{
	double	prod;
	double	div;
	int		i;

	if (val == 0)
		return (0);
	i = 0;
	div = 1;
	if (n < 0)
		div = -1;
	prod = 1;
	while (i != n)
	{
		if (n > 0)
			prod = prod * val;
		else
			prod = prod / val;
		i += div;
	}
	return (prod);
}

long	ft_gcd(long a, long b)
{
	if (b == 0)
		return (a);
	else
		return (ft_gcd(b, a % b));
}
