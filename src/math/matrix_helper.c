/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:23:05 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 18:11:19 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_matrix_free(t_matrix *matrix)
{
	uint32_t	i;

	if (!matrix || !(matrix->n) || !(matrix->m))
		return ;
	if (!(matrix->matrix))
		return ;
	i = 0;
	while (i < matrix->m)
	{
		if (matrix->matrix[i])
			free(matrix->matrix[i]);
	}
	free(matrix->matrix);
}

int	ft_matrix_init(t_matrix *matrix, uint32_t m, uint32_t n)
{
	uint32_t	i;
	int			ret;

	if (!matrix || !m || !n)
		return (-1);
	matrix->m = m;
	matrix->n = n;
	matrix->matrix = (t_cd **)malloc(m * sizeof(t_cd *));
	if (!(matrix->matrix))
		return (-1);
	i = 0;
	ret = 0;
	while (i < m && ret > -1)
	{
		(matrix->matrix)[i] = (t_cd *)calloc(n, sizeof(t_cd));
		if (!((matrix->matrix)[i]))
			ret = -1;
	}
	if (ret < 0)
		ft_matrix_free(matrix);
	return (ret);
}

int	ft_matrix_add(t_matrix *out, t_matrix *m1, t_matrix *m2, uint8_t sub)
{
	long	i;
	long	j;

	if (!m1 || !m2 || !out)
		return (-1);
	if (m1->m != m2->m || m1->n != m2->n)
		return (-1);
	if (ft_matrix_init(out, m1->m, m1->n) == -1)
		return (-1);
	i = -1;
	while (++i < out->m)
	{
		j = -1;
		while (++j < out->n)
			ft_cd_add(out->matrix[i] + j,
				m1->matrix[i][j], m2->matrix[i][j], sub);
	}
	return (0);
}

int	ft_matrix_scalar_mult(t_matrix *out, t_matrix *m1, double num)
{
	long	i;
	long	j;
	t_cd	c;

	if (!out || !m1)
		return (-1);
	if (ft_matrix_init(out, m1->m, m1->n) == -1)
		return (-1);
	c.real = num;
	c.imag = 0;
	i = -1;
	while (++i < out->m)
	{
		j = -1;
		while (++j < out->n)
			ft_cd_mult(out->matrix[i] + j, m1->matrix[i][j], c);
	}
	return (0);
}

int	ft_matrix_mult(t_matrix *out, t_matrix *m1, t_matrix *m2)
{
	long	i;
	long	j;
	long	k;
	t_cd	c;

	if (!out || !m1 || !m2 || (m1->n != m2->m))
		return (-1);
	if (ft_matrix_init(out, m1->m, m2->n) == -1)
		return (-1);
	i = -1;
	while (++i < out->m)
	{
		j = -1;
		while (++j < out->n)
		{
			ft_cd_init(out->matrix[i] + j, 0.0, 0.0);
			k = -1;
			while (++k < m1->n)
			{
				ft_cd_mult(&c, m1->matrix[i][k], m2->matrix[k][j]);
				ft_cd_add(out->matrix[i] + j, out->matrix[i][j], c, 0);
			}
		}
	}
	return (0);
}
