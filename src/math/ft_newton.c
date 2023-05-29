/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:08:29 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 18:21:20 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

double	ft_get_val_x(double x, t_poly *poly)
{
	int		i;
	double	val;

	val = 0;
	i = -1;
	while (++i <= poly->degree)
		val += (poly->coff[i]) * (ft_pow(x, i));
	return (val);
}

double	ft_newton_root(t_poly *p, t_poly *p_prime)
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
		if (val_x == val_prime_x || val_prime_x == 0)
			break ;
		xn = xn1 - (val_x / val_prime_x);
		xn1 = xn;
	}
	return (xn);
}

double	ft_rt(double num, int8_t pow)
{
	t_poly	p;
	t_poly	p_prime;
	double	val;

	if (pow < 0)
		return (-1);
	if (!num || (num == 1))
		return (num);
	if (pow == 0)
		return (1);
	if (ft_poly_init(&p, pow, 0) == -1)
		return (-1);
	if (ft_poly_init(&p_prime, pow - 1, 0) == -1)
		return (-1);
	p.coff[pow] = 1;
	p.coff[0] = -1 * num;
	p_prime.coff[pow - 1] = pow;
	val = ft_newton_root(&p, &p_prime);
	ft_poly_free(&p);
	ft_poly_free(&p_prime);
	return (val);
}
