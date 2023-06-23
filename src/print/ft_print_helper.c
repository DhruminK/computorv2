/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:07:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 14:12:21 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_print_complex(t_cd *c, uint8_t in_poly, uint8_t is_first)
{
	int	mult;

	if (!c)
		return ;
	mult = 1;
	if (c->real < 0.0 && in_poly)
		mult = -1;
	if (c->real < 0.0 && in_poly)
		printf(" - ");
	else if (in_poly && !is_first)
		printf(" + ");
	if (in_poly && c->imag != 0.0)
		printf("(");
	printf("%0.1f", c->real * mult);
	if (c->imag * mult < 0.0)
		printf(" - %0.1fi", c->imag * mult * -1);
	else if (c->imag * mult > 0.0)
		printf(" + %0.1fi", c->imag * mult);
	if (in_poly && c->imag != 0.0)
		printf(")");
}

/**
void	ft_print_poly(t_poly *poly)
{
	int	i;

	if (!poly || poly->degree < 0 || !(poly->coff))
		return ;
	ft_print_complex(poly->coff, 0);
	i = 0;
	while (++i <= poly->degree)
	{
		ft_print_complex(poly->coff + i, 1);
		printf("x ^ %d", i);
	}
}
*/

void	ft_print_poly(t_poly *poly)
{
	t_list		*ele;
	t_poly_var	*pvar;
	char		*v;
	uint8_t		b;

	if (!poly || !(poly->coff))
	{
		printf("0");
		return ;
	}
	v = "x";
	b = 1;
	if (poly->var_name)
		v = poly->var_name;
	ele = poly->coff;
	while (ele)
	{
		pvar = (t_poly_var *)(ele->content);
		ft_print_complex(&(pvar->coff), 1, b);
		if (pvar->degree != 0.0)
			printf(" * %s^%0.0f", v, pvar->degree);
		b = 0;
		ele = ele->next;
	}
}

void	ft_print_matrix(t_matrix *matrix)
{
	uint32_t	i;
	uint32_t	j;

	if (!matrix || !(matrix->matrix)
		|| !(matrix->m) || !(matrix->n))
		return ;
	i = 0;
	while (i < matrix->m)
	{
		j = 0;
		printf("[");
		while (j < matrix->n)
		{
			ft_print_var(&(matrix->matrix[i][j]), 0);
			if (j != matrix->n - 1)
				printf(" , ");
			j += 1;
		}
		printf("]\n");
		i += 1;
	}
}

void	ft_print_var(t_var *v, uint8_t nl)
{
	if (!v)
		return ;
	if (v->type == CV2_MATRIX)
		return (ft_print_matrix(&(v->choice.matrix)));
	else if (v->type == CV2_RATIONAL || v->type == CV2_COMPLEX)
	{
		if (v->choice.poly.coff)
			ft_print_complex(&((t_poly_var *)
					(v->choice.poly.coff->content))->coff, 0, 0);
		else
			printf("0");
	}
	else if (v->type == CV2_OP || v->type == CV2_NONE)
		printf("This should not be printed: %c\n", v->choice.ch);
	else
		(ft_print_poly(&(v->choice.poly)));
	if (nl)
		printf("\n");
}
