/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:11:51 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 15:31:45 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_parse_func_arg(t_var *out, char **inp, t_poly_op *poly_op)
{
	t_poly_inp	poly_inp;

	if (!inp || !out || !poly_op || !(poly_op->poly_inp))
		return (-1);
	memset(&poly_inp, 0, sizeof(t_poly_inp));
	poly_inp.vars_avail = poly_op->poly_inp->vars_avail;
	poly_inp.inp = *inp;
	poly_inp.var_name = poly_op->poly_inp->var_name;
	poly_inp.end_char = ')';
	if (ft_parse_poly(&poly_inp) == -1)
		return (-1);
	memcpy(out, &(poly_inp.out), sizeof(t_var));
	(*inp) = (poly_inp.inp + 1);
	return (0);
}

int	ft_parse_func_var(t_var *func, char **inp, t_poly_op *poly_op)
{
	t_var	arg;
	t_var	out;
	int		ret;

	if (!func || !inp || !poly_op)
		return (-1);
	memset(&out, 0, sizeof(t_var));
	memset(&arg, 0, sizeof(t_var));
	if (ft_parse_inp_move(inp) != 9)
		return (-1);
	(*inp) += 1;
	if (ft_parse_func_arg(&arg, inp, poly_op) == -1)
		return (-1);
	ret = ft_process_func_op(&out, func, &arg);
	if (arg.type == CV2_POLY || arg.type == CV2_FUNC)
		out.type = CV2_FUNC;
	if (ret != -1)
		ret = ft_stack_push(&(poly_op->stack_vars), &out);
	poly_op->prev_type = out.type;
	ft_var_free(&arg);
	if (ret == -1)
		ft_var_free(&out);
	return (ret);
}
