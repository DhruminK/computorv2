/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_poly_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:34:18 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/23 20:37:21 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_parse_poly_find_degree(char **inp, double *degree)
{
	int	ret;

	if (!inp || !degree)
		return (-1);
	*degree = 1;
	ret = ft_parse_inp_move(inp);
	if (ret != 8)
		return (0);
	(*inp) += 1;
	*degree = 0.0;
	ft_parse_num(inp, degree, 0);
	return (0);
}

static int	ft_parse_poly_var_name_validate(char **inp, double *deg,
				char *var_name)
{
	int		ret;
	char	*s;

	if (!inp || !var_name || !deg)
		return (-1);
	s = (*inp) + strlen(var_name);
	ret = ft_valid(*s);
	if (ret == 1 || ret == 2)
		return (0);
	*inp = s;
	ret = ft_parse_poly_find_degree(inp, deg);
	if (ret == -1)
		return (-1);
	return (1);
}

static int	ft_poly_var_name_process(t_poly_op *poly_op, int ret)
{
	if (!poly_op)
		return (-1);
	if (ret < 1)
		return (ret);
	if (poly_op->prev_type != CV2_NONE && poly_op->prev_type != CV2_OP
		&& ft_add_op_stack(poly_op, '*') == -1)
		return (-1);
	return (ret);
}

int	ft_parse_poly_var(char **inp, t_poly_op *poly_op, char *var_name)
{
	double	deg;
	t_var	v;
	int		ret;
	t_cd	coff;

	if (!inp || !poly_op || !var_name)
		return (-1);
	ret = ft_parse_poly_var_name_validate(inp, &deg, var_name);
	ret = ft_poly_var_name_process(poly_op, ret);
	if (ret < 1)
		return (ret);
	ft_cd_init(&coff, 1, 0);
	v.var_name = 0;
	v.type = CV2_POLY;
	ft_poly_init(&(v.choice.poly), 0, var_name);
	if (ft_poly_var_init(&(v.choice.poly), deg, coff) == -1)
		return (-1);
	ret = ft_stack_push(&(poly_op->stack_vars), &v);
	if (ret == -1)
		ft_var_free(&v);
	if (ret == -1)
		return (-1);
	poly_op->prev_type = v.type;
	return (1);
}
