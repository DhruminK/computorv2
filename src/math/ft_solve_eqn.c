/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_eqn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:05:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/22 17:27:57 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_validate_eqn(t_var *v, t_cd *coff)
{
	t_poly		*p;
	t_poly_var	*pvar;
	t_list		*ele;

	if (!coff || !v || v->type == CV2_MATRIX)
		return (-1);
	memset(coff, 0, sizeof(t_cd) * 3);
	p = &(v->choice.poly);
	if (p->max_degree > 2 || p->min_degree < 0 || p->contain_root == 1)
		return (-1);
	ele = p->coff;
	while (ele)
	{
		pvar = (t_poly_var *)(ele->content);
		if (pvar->degree != 0 && pvar->degree != 1 && pvar->degree != 2)
			return (-1);
		memcpy(coff + (int)(pvar->degree), &(pvar->coff), sizeof(t_cd));
		ele = ele->next;
	}
	return (0);
}

static int	ft_determinant(t_var *v, t_cd *det, t_cd *coff)
{
	t_cd	minus;
	double	out;
	int		m;

	if (!coff || !det || ft_validate_eqn(v, coff) == -1)
		return (-1);
	ft_cd_mult(det, coff[1], coff[1]);
	ft_cd_mult(&minus, coff[0], coff[2]);
	ft_cd_scalar_mult(&minus, 4, minus);
	ft_cd_add(det, *det, minus, 1);
	if (det->imag != 0)
		return (-1);
	m = 1;
	if (det->real < 0)
		m = -1;
	if (ft_gen_pow(det->real * m, 0.5, &out) == -1)
		return (-1);
	memset(det, 0, sizeof(t_cd));
	if (m == 1)
		det->real = out;
	else
		det->imag = out;
	return (0);
}

int	ft_solve_eqn(t_var *v)
{
	t_cd	coff[3];
	t_cd	des;

	if (!v)
		return (-1);
	printf("Simplified equations : ");
	ft_print_var(v, 0);
	printf(" = %0.1f\n", 0.0);
	if (ft_determinant(v, &des, (t_cd *)coff) == -1)
		return (-1);
	if (coff[2].real == 0 && coff[2].imag == 0
		&& coff[1].real == 0 && coff[2].imag == 0)
		ft_solve_outlier(coff[0]);
	else if (coff[2].real == 0 && coff[2].imag == 0)
		ft_solve_linear(coff);
	else
		ft_solve_quad((t_cd *)coff, &des);
	return (0);
}
