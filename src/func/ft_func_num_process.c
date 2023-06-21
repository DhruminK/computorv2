/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_num_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:25:26 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/21 15:05:54 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_func_process_single_pvar(t_var *out, t_var *arg,
				t_poly_var *pvar)
{
	t_var	pow;
	t_var	coff;
	t_var	tmp_out;
	int		ret;

	if (!arg || !pvar || !out)
		return (-1);
	memset(&pow, 0, sizeof(t_var));
	memset(&coff, 0, sizeof(t_var));
	memset(&tmp_out, 0, sizeof(t_var));
	ret = ft_var_num_init(&pow, pvar->degree, 0);
	if (ret != -1)
		ret = ft_var_num_init(&coff, 0, &(pvar->coff));
	if (ret != -1 && pvar->degree != 0)
		ret = ft_var_op_wo_free(&tmp_out, &pow, arg, '^');
	else if (ret != 1 && pvar->degree == 0)
		ret = ft_var_num_init(&tmp_out, 1, 0);
	if (ret != -1)
		ret = ft_var_op_wo_free(out, &coff, &tmp_out, '*');
	ft_var_free(&pow);
	ft_var_free(&coff);
	ft_var_free(&tmp_out);
	return (ret);
}

/**
static int	ft_func_num_process_loop_pvar(t_var *out, t_var *arg,
				t_list *func_list)
{
	t_poly_var	*pvar;
	t_var		tmp_out;
	t_var		tmp_out1;
	int			ret;

	if (!out || !arg || !func_list)
		return (-1);
	while (func_list)
	{
		pvar = (t_poly_var *)(func_list->content);
		ret = ft_func_process_single_pvar(&tmp_out, arg, pvar);
		if (ret != -1)
			ret = ft_var_op(out, &tmp_out1, &tmp_out, '+');
		if (ret != -1)
			ret = ft_var_cpy_no_name(&tmp_out1, out);
		if (ret == -1)
			break ;
		func_list = func_list->next;
	}
	if (ret == -1)
		ft_var_free(out);
	ft_var_free(&tmp_out);
	ft_var_free(&tmp_out1);
	return (ret);
}
*/

static int	ft_func_num_process_loop_pvar(t_var *out, t_var *arg,
				t_list *func_list)
{
	t_poly_var	*pvar;
	t_var		tmp_out;
	t_var		tmp_out1;
	int			ret;

	if (!out || !arg || !func_list)
		return (-1);
	ret = ft_var_num_init(&tmp_out1, 0, 0);
	while (func_list && ret != -1)
	{
		pvar = (t_poly_var *)(func_list->content);
		ret = ft_func_process_single_pvar(&tmp_out, arg, pvar);
		if (ret != -1)
			ret = ft_var_op(out, &tmp_out1, &tmp_out, '+');
		memcpy(&tmp_out1, out, sizeof(t_var));
		func_list = func_list->next;
	}
	if (ret == -1)
		ft_var_free(out);
	return (ret);
}

int	ft_func_num_process(t_var *out, t_var *func, t_var *arg)
{
	t_poly	*p;

	if (!out || !func || !arg || arg->type != CV2_RATIONAL
		|| func->type != CV2_FUNC)
		return (-1);
	p = &(func->choice.poly);
	if (!(p->coff))
		return (ft_var_num_init(out, 0, 0));
	return (ft_func_num_process_loop_pvar(out, arg, p->coff));
}
