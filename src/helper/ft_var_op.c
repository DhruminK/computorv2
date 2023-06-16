/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:04:08 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 18:24:48 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_var_matrix_op(t_var *out, t_var *v1, t_var *v2, char op)
{
	if (!out || !v1 || !v2 || v1->type == CV2_NONE || v1->type == CV2_OP
		|| v2->type == CV2_NONE || v2->type == CV2_OP)
		return (-1);
	out->type = CV2_MATRIX;
	if ((op == '+' || op == '-' || op == 'm' || op == 'M')
		&& (v1->type != CV2_MATRIX || v2->type != CV2_MATRIX))
		return (-1);
	if (op == '+' || op == '-')
		return (ft_matrix_add(&(out->choice.matrix),
				&(v1->choice.matrix), &(v2->choice.matrix), op == '-'));
	if (op == 'M' || op == 'm')
		return (ft_matrix_mult(&(out->choice.matrix),
				&(v1->choice.matrix), &(v2->choice.matrix)));
	/**
	if (op == '*' && (v1->type == CV2_MATRIX && v2->type != CV2_MATRIX))
		return (ft_matrix_scalar_mult(&(out->choice.matrix),
				&(v1->choice.matrix), v2->choice.poly.coff[0].real));
	if (op == '*' && (v1->type != CV2_MATRIX && v2->type == CV2_MATRIX))
		return (ft_matrix_scalar_mult(&(out->choice.matrix),
				&(v2->choice.matrix), v1->choice.poly.coff[0].real));
				*/
	return (-1);
}

static int	ft_var_validate_poly(t_var *out, t_var *v1, t_var *v2)
{
	if (!out || !v1 || !v2)
		return (-1);
	if (!(v1->type == CV2_POLY || v1->type == CV2_FUNC
			|| v1->type == CV2_COMPLEX || v1->type == CV2_RATIONAL))
		return (-1);
	if (!(v2->type == CV2_POLY || v2->type == CV2_FUNC
			|| v2->type == CV2_COMPLEX || v2->type == CV2_RATIONAL))
		return (-1);
	out->type = CV2_RATIONAL;
	if (v1->type == CV2_FUNC || v2->type == CV2_FUNC)
		out->type = CV2_FUNC;
	else if (v1->type == CV2_POLY || v2->type == CV2_POLY)
		out->type = CV2_POLY;
	else if (v1->type == CV2_COMPLEX || v2->type == CV2_COMPLEX)
		out->type = CV2_COMPLEX;
	return (0);
}

static int	ft_var_poly_op(t_var *out, t_var *v1, t_var *v2, char op)
{
	if (!out || !v1 || !v2 || ft_var_validate_poly(out, v1, v2) == -1)
		return (-1);
	if (op == '+' || op == '-')
		return (ft_poly_add(&(out->choice.poly), &(v1->choice.poly),
				&(v2->choice.poly), op == '-'));
	else if (op == '*')
		return (ft_poly_mult(&(out->choice.poly), &(v1->choice.poly),
				&(v2->choice.poly)));
	else if (op == '/')
		return (ft_poly_div(&(out->choice.poly), &(v1->choice.poly),
				&(v2->choice.poly)));
	else if (op == '^')
		return (ft_poly_pow(&(out->choice.poly), &(v1->choice.poly),
				&(v2->choice.poly)));
	return (-1);
}

int	ft_var_op(t_var *out, t_var *v1, t_var *v2, char op)
{
	int	ret;

	if (!out || !v1 || !v2)
		return (-1);
	out->var_name = 0;
	ret = 1;
	if (v1->type == CV2_MATRIX || v2->type == CV2_MATRIX)
		ret = ft_var_matrix_op(out, v2, v1, op);
	if (ret == 1)
		ret = ft_var_poly_op(out, v2, v1, op);
	if (ret == -1)
		return (-1);
	ft_var_free(v1);
	ft_var_free(v2);
	return (0);
}

int	ft_var_op_wo_free(t_var *out, t_var *v1, t_var *v2, char op)
{
	int	ret;

	if (!out || !v1 || !v2)
		return (-1);
	out->var_name = 0;
	ret = 1;
	if (v1->type == CV2_MATRIX || v2->type == CV2_MATRIX)
		ret = ft_var_matrix_op(out, v2, v1, op);
	if (ret == 1)
		ret = ft_var_poly_op(out, v2, v1, op);
	if (ret == -1)
		return (-1);
	return (0);
}
