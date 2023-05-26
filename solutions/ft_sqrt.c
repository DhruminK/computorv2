/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:32:53 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/09 19:13:12 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static double	ft_get_val_x(double x, t_poly *poly)
{
	int		i;
	double	val;

	val = 0;
	i = -1;
	while (++i <= poly->degree)
		val += (poly->coff[i]) * (ft_pow(x, i));
	return (val);
}

static double	ft_find_sqrt(t_poly *p, t_poly *p_prime)
{
	double	xn1;
	double	xn;
	double	val_x;
	double	val_prime_x;
	int		i;

	xn1 = p->coff[0];
	if (xn1 < 0)
		xn1 *= -1;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		val_x = ft_get_val_x(xn1, p);
		val_prime_x = ft_get_val_x(xn1, p_prime);
		xn = xn1 - (val_x / val_prime_x);
		if (xn == xn1)
			break ;
		xn1 = xn;
	}
	return (xn);
}

double	ft_sqrt(double num)
{
	t_poly	p;
	t_poly	p_prime;
	double	val;

	if (!num || (num == 1))
		return (num);
	if (ft_init_2deg_poly(&p, -1 * num, 0, 1) == -1)
		return (-1);
	if (ft_get_derivative(&p, &p_prime) == -1)
		return (-1);
	val = ft_find_sqrt(&p, &p_prime);
	free(p_prime.coff);
	free(p.coff);
	return (val);
}
