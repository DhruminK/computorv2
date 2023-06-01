/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:32:59 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 18:56:22 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

double	ft_pow(double val, int n)
{
	int		i;
	int		n1;
	double	prod;

	if (!val)
		return (val);
	if (!n)
		return (1);
	prod = 1;
	n1 = n;
	if (n < 0)
		n1 *= -1;
	i = -1;
	while (++i < n1)
	{
		if (n < 0)
			prod /= val;
		else
			prod *= val;
	}
	return (prod);
}

void	ft_frac(double n, long *numr, long *deno)
{
	double	frac;
	double	integer;

	if (!numr || !deno)
		return ;
	(*numr) = 0;
	(*deno) = 1;
	if (n == 0.0)
		return ;
	frac = n - (long)n;
	integer = (n - frac);
	while (frac != 0.0)
	{
		(*deno) *= 10;
		frac *= 10;
		integer = (frac) - (frac - (long)frac);
		(*numr) = ((*numr) * 10) + integer;
		frac = frac - (long)frac;
	}
	integer = n - (n - (long)n);
	(*numr) += ((long)integer) * (*deno);
}

double	ft_gen_pow(double val, double pow)
{
	long	numr;
	long	deno;
	double	prod;
	double	n;

	if (val == 0.0)
		return (val);
	if (pow == 0.0)
		return (1);
	n = pow;
	if (n < 0)
		n *= -1;
	ft_frac(n, &numr, &deno);
	prod = ft_pow(val, (int)numr);
	if (deno > 1)
		prod = ft_rt(prod, (int8_t)deno);
	if (n < 0)
		prod = 1 / prod;
	return (prod);
}

int	ft_get_derivative(t_poly *poly, t_poly *deri)
{
	int	i;

	if (!poly || !deri)
		return (-1);
	if (poly->degree == 1)
		return (-1);
	deri->degree = poly->degree - 1;
	deri->coff = malloc(sizeof(double) * (deri->degree + 1));
	if (!(deri->coff))
		return (-1);
	i = -1;
	while (++i <= deri->degree)
		deri->coff[i].real = poly->coff[i + 1].real * (i + 1);
	return (0);
}

int	ft_init_2deg_poly(t_poly *poly, double coff0,
		double coff1, double coff2)
{
	if (!poly)
		return (-1);
	poly->degree = 2;
	poly->coff = calloc(3, sizeof(t_cd));
	poly->coff[0].real = coff0;
	poly->coff[1].real = coff1;
	poly->coff[2].real = coff2;
	return (0);
}
