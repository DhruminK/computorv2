/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:50:54 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:13:37 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_poly_init(t_poly *poly, int8_t degree, char *name)
{
	if (!poly || degree < 0)
		return (-1);
	poly->name = 0;
	if (name)
	{
		poly->name = strdup(name);
		if (!(poly->name))
			return (-1);
	}
	poly->degree = 0;
	poly->coff = (t_cd *)calloc(poly->degree + 1, sizeof(t_cd));
	if (!poly->coff)
		return (-1);
	return (0);
}

int	ft_poly_cpy(t_poly *dst, t_poly *src)
{
	if (!dst || !src)
		return (-1);
	if (ft_poly_init(dst, src->degree, 0) == -1)
		return (-1);
	memcpy(dst->coff, src->coff, sizeof(t_cd) * (src->degree + 1));
	return (0);
}

void	ft_poly_free(t_poly *poly)
{
	if (!poly)
		return ;
	if (poly->name)
		free(poly->name);
	if (poly->coff)
		free(poly->coff);
	memset(poly, 0, sizeof(t_poly));
}

int	ft_poly_add(t_poly *out, t_poly *p1, t_poly *p2, uint8_t sub)
{
	int	i;

	if (!out || !p1 || !p2 || p1 == out || p2 == out)
		return (-1);
	memcpy(out, p1, sizeof(t_poly));
	if (out->degree < p2->degree)
		out->degree = p2->degree;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	memcpy(out->coff, p1->coff, sizeof(t_cd) * (p1->degree + 1));
	i = -1;
	while (++i <= p2->degree)
		ft_cd_add(out->coff + i, out->coff[i], p2->coff[i], sub);
	return (0);
}

int	ft_poly_mult(t_poly *out, t_poly *p1, t_poly *p2)
{
	int		i;
	int		j;
	t_cd	c;

	if (!out || !p1 || !p2 || p1 == out || p2 == out)
		return (-1);
	out->degree = p1->degree + p2->degree;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	i = -1;
	while (++i <= p1->degree)
	{
		j = -1;
		while (++j <= p2->degree)
		{
			ft_cd_mult(&c, p1->coff[i], p2->coff[j]);
			ft_cd_add(out->coff + i + j, out->coff[i + j], c, 0);
		}
	}
	return (0);
}
