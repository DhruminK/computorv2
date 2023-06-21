/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:04:53 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/21 14:43:35 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_matrix_cpy(t_matrix *dst, t_matrix *src)
{
	uint32_t	i;
	uint32_t	j;

	if (!dst || !src)
		return (-1);
	if (ft_matrix_init(dst, src->m, src->n) == -1)
		return (-1);
	i = 0;
	while (i < src->m)
	{
		j = 0;
		while (j < src->n)
		{
			if (ft_var_cpy_no_name(&(dst->matrix[i][j]),
				&(src->matrix[i][j])) == -1)
				return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}

int	ft_var_cpy_no_name(t_var *dst, t_var *src)
{
	int	ret;

	if (!dst || !src)
		return (-1);
	memset(dst, 0, sizeof(t_var));
	dst->type = src->type;
	ret = 0;
	if (dst->type == CV2_MATRIX)
		ret = ft_matrix_cpy(&(dst->choice.matrix), &(src->choice.matrix));
	else if (dst->type != CV2_MATRIX && dst->type != CV2_NONE
		&& dst->type != CV2_OP)
		ret = ft_poly_cpy(&(dst->choice.poly), &(src->choice.poly));
	else
		memcpy(&(dst->choice), &(src->choice), sizeof(t_vars));
	return (ret);
}

int	ft_var_num_init(t_var *v, double real, t_cd *coff)
{
	t_cd	c;

	if (!v)
		return (-1);
	memset(v, 0, sizeof(t_var));
	v->type = CV2_RATIONAL;
	if (coff && coff->imag != 0.0)
		v->type = CV2_COMPLEX;
	memset(&c, 0, sizeof(t_cd));
	if (!coff)
		c.real = real;
	else
		memcpy(&c, coff, sizeof(t_cd));
	ft_poly_init(&(v->choice.poly), 0, 0);
	if (ft_poly_var_init(&(v->choice.poly), 0, c) == -1)
		return (-1);
	return (0);
}
