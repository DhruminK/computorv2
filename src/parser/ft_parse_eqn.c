/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_eqn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:10:42 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/23 20:47:41 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_search_var_name(char **inp, char **var_name, t_list *vars)
{
	t_var	*v;
	int		ret;
	int		i;

	if (!inp || !var_name || ft_valid(*(*inp)) != 1)
		return (-1);
	ret = 1;
	i = -1;
	while (ret == 1 || ret == 2)
		ret = ft_valid((*inp)[++i]);
	*var_name = strndup((*inp), i);
	if (!*var_name)
		return (-1);
	ret = ft_find_var_from_name(*var_name, vars, &v);
	if (ret == -1 || ret == 1)
		free(*var_name);
	(*inp) += i;
	return (ret);
}

static int	ft_find_unkown_var(t_list *vars, char *buf, char **var_name)
{
	int	val;
	int	ret;

	if (!buf || !var_name)
		return (-1);
	*var_name = 0;
	ret = 1;
	while (*buf)
	{
		val = ft_valid(*buf);
		if (val == 1)
			ret = ft_search_var_name(&buf, var_name, vars);
		if (ret < 1)
			return (ret);
		if (val != 1)
			buf += 1;
	}
	*var_name = 0;
	return (1);
}

static int	ft_parse_lhs_rhs(char *buf, t_var *out,
				t_list *vars, char *var_name)
{
	t_poly_inp	pi;
	t_var		lhs;
	int			ret;

	if (!buf || !out)
		return (-1);
	memset(out, 0, sizeof(t_var));
	pi.var_name = var_name;
	pi.vars_avail = vars;
	pi.inp = buf;
	pi.end_char = '=';
	if (ft_parse_poly(&pi) == -1)
		return (-1);
	memcpy(&lhs, &(pi.out), sizeof(t_var));
	pi.end_char = '?';
	pi.inp += 1;
	ret = ft_parse_poly(&pi);
	if (!ret)
		ret = ft_var_op(out, &(pi.out), &lhs, '-');
	if (!ret)
		return (0);
	ft_var_free(&lhs);
	ft_var_free(&(pi.out));
	ft_var_free(out);
	return (-1);
}

int	ft_parse_eqn(char *buf, t_list *vars)
{
	int		ret;
	t_var	out;
	char	*var_name;

	if (!buf)
		return (-1);
	memset(&out, 0, sizeof(t_var));
	ret = ft_find_unkown_var(vars, buf, &(var_name));
	if (ret == -1)
		return (-1);
	if (ret == 1)
		var_name = 0;
	ret = ft_parse_lhs_rhs(buf, &out, vars, var_name);
	if (ret != -1)
		ret = ft_solve_eqn(&out);
	if (var_name)
		free(var_name);
	ft_var_free(&out);
	return (ret);
}
