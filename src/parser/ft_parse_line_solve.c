/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line_solve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:23:01 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/22 17:17:38 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_parse_line_solve(char *buf, t_list *vars, t_var *out)
{
	t_var		lhs;
	t_poly_inp	pi;
	int			ret;

	memset(out, 0, sizeof(t_var));
	memset(&lhs, 0, sizeof(t_var));
	memset(&pi, 0, sizeof(t_poly_inp));
	pi.vars_avail = vars;
	pi.inp = buf;
	pi.end_char = '=';
	if (ft_parse_poly(&pi) == -1)
		return (-1);
	memcpy(&lhs, &(pi.out), sizeof(t_var));
	pi.inp += 1;
	pi.end_char = '?';
	ret = ft_parse_poly(&pi);
	if (!ret)
		ret = ft_var_op(out, &(pi.out), lhs, '-');
	if (!ret)
		return (0);
	ft_var_free(&lhs);
	ft_var_free(&(pi.out));
	ft_var_free(out);
	return (-1);
}

int	ft_process_line_solve(char *buf, t_list *vars)
{
	t_var	out;

	if (!buf)
		return (-1);
	if (ft_parse_line_solve(buf, vars, &out) == -1)
		return (-1);
}
