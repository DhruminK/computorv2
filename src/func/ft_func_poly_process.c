/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_poly_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:26:21 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/23 18:51:41 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_func_var_pow_loop(t_var *out, t_var *arg, int degree, int div)
{
	t_var	tmp_out;
	char	op;
	int		ret;

	if (!out || !arg || !degree || (div != 1 && div != -1))
		return (-1);
	ret = 0;
	op = '*';
	if (degree < 0)
		op = '/';
	while (degree != 0 && ret != -1)
	{
		ret = ft_var_op_wo_free(&tmp_out, out, arg, op);
		ft_var_free(out);
		memcpy(out, &tmp_out, sizeof(t_var));
		memset(&tmp_out, 0, sizeof(t_var));
		degree += div;
	}
	return (ret);
}

static int	ft_func_var_pow(t_var *out, t_var *arg, int degree)
{
	int		ret;
	int		div;

	if (!out || !arg)
		return (-1);
	ret = ft_var_num_init(out, 1, 0);
	if (ret == -1 || !degree)
		return (ret);
	div = -1;
	if (degree < 0)
		div = 1;
	ret = ft_func_var_pow_loop(out, arg, degree, div);
	if (ret == -1)
		ft_var_free(out);
	return (ret);
}

static int	ft_func_poly_single_pvar(t_var *out, t_var *arg, t_poly_var *pvar)
{
	t_var	coff;
	t_var	tmp_out;
	int		ret;

	if (!out || !arg || !pvar)
		return (-1);
	if ((pvar->degree) - (long)(pvar->degree) != 0.0)
		return (-1);
	memset(&coff, 0, sizeof(t_var));
	memset(&tmp_out, 0, sizeof(t_var));
	ret = ft_var_num_init(&coff, 0, &(pvar->coff));
	if (ret != -1)
		ret = ft_func_var_pow(&tmp_out, arg, (int)pvar->degree);
	if (ret != -1)
		ret = ft_var_op(out, &coff, &tmp_out, '*');
	ft_var_free(&tmp_out);
	ft_var_free(&coff);
	if (ret == -1)
		ft_var_free(out);
	return (ret);
}

static int	ft_func_poly_pvar_loop(t_var *out, t_var *arg, t_list *func)
{
	t_poly_var	*pvar;
	t_var		tmp_out;
	t_var		tmp_out1;
	int			ret;

	if (!out || !arg || !func)
		return (-1);
	memset(&tmp_out, 0, sizeof(t_var));
	ret = ft_var_num_init(&tmp_out1, 0, 0);
	while (func && ret != -1)
	{
		pvar = (t_poly_var *)(func->content);
		ret = ft_func_poly_single_pvar(&tmp_out, arg, pvar);
		if (ret != -1)
			ret = ft_var_op(out, &tmp_out1, &tmp_out, '+');
		if (ret != -1)
			ret = ft_var_cpy_no_name(&tmp_out1, out);
		func = func->next;
	}
	if (ret == -1)
		ft_var_free(out);
	ft_var_free(&tmp_out);
	ft_var_free(&tmp_out1);
	return (ret);
}

int	ft_func_poly_process(t_var *out, t_var *func, t_var *arg)
{
	t_poly	*p;

	if (!out || !func || !arg || (arg->type != CV2_POLY
			&& arg->type != CV2_COMPLEX && arg->type != CV2_FUNC))
		return (-1);
	p = &(func->choice.poly);
	if (!(p->coff))
		return (ft_var_num_init(out, 0, 0));
	if (p->contain_root)
		return (-1);
	return (ft_func_poly_pvar_loop(out, arg, p->coff));
}
