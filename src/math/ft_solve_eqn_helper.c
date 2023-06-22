/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_eqn_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:40:08 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/22 17:32:11 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_solve_linear(t_cd *coff)
{
	t_cd	out;

	if (!coff || (coff[1].real == 0 && coff[1].imag == 0))
		return ;
	ft_cd_div(&out, coff[0], coff[1]);
	ft_cd_scalar_mult(&out, -1, out);
	printf("Polynomial Degree: 1\n");
	printf("The solution is :\n");
	ft_print_complex(coff, 0, 1);
	printf("\n");
}

void	ft_solve_outlier(t_cd c)
{
	if (c.real == 0 && c.imag == 0)
		printf("This polynomial has infinite solutions\n");
	else
		printf("This polynomial has no solutions\n");
}

static void	ft_solve_quad_non_zero_det(t_cd *root, t_cd *des)
{
	t_cd	out;

	if (!root || !des)
		return ;
	ft_cd_mult(&out, *des, *des);
	if (des->real == 0.0)
		printf("Discriminant is strictly negative = %.6f"
			", the two solutions are :\n", out.real);
	else
		printf("Discriminant is strictly positive = %.6f"
			", the two solutions are :\n", out.real);
	ft_print_complex(root, 0, 1);
	printf("\n");
	ft_print_complex(root + 1, 0, 1);
	printf("\n");
}

void	ft_solve_quad(t_cd *coff, t_cd *des)
{
	t_cd	root[2];
	t_cd	minus;

	if (!coff || (coff[2].real == 0 && coff[2].imag == 0))
		return ;
	ft_cd_scalar_mult(&minus, -1, coff[1]);
	ft_cd_add(root, minus, *des, 0);
	ft_cd_div(root, root[0], coff[2]);
	ft_cd_scalar_mult(root, 0.5, root[0]);
	ft_cd_add(root + 1, minus, *des, 1);
	ft_cd_div(root + 1, root[1], coff[2]);
	ft_cd_scalar_mult(root + 1, 0.5, root[1]);
	if (des->real == 0 && des->imag == 0)
	{
		printf("Discriminant is zero, the single solution is :\n");
		ft_print_complex(root, 0, 1);
		printf("\n");
	}
	else
		return (ft_solve_quad_non_zero_det((t_cd *)root, des));
}
