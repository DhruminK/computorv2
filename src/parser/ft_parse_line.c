/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:29:20 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/24 13:57:10 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_process_line_type(char *buf)
{
	char	*eq;
	char	*qs;

	if (!buf)
		return (-1);
	eq = strchr(buf, '=');
	qs = strchr(buf, '?');
	if (qs && eq && eq > qs)
		return (-1);
	if (qs && eq)
		return (0);
	if (eq)
		return (1);
	return (2);
}

static int	ft_parse_line_poly(char *buf, t_list *vars)
{
	t_poly_inp	inp;

	if (!buf)
		return (-1);
	memset(&inp, 0, sizeof(t_poly_inp));
	inp.vars_avail = vars;
	inp.inp = buf;
	if (ft_parse_poly(&inp) == -1)
		return (-1);
	ft_print_var(&(inp.out), 1);
	ft_var_free(&(inp.out));
	return (0);
}

int	ft_process_line(char *buf, t_list **vars)
{
	int	ret;

	if (!buf || !vars)
		return (-1);
	ret = ft_process_line_type(buf);
	if (ret == -1)
		return (-1);
	if (ret == 0)
		return (ft_error_print(3, ft_parse_eqn(buf, *vars)));
	if (ret == 1)
		return (ft_error_print(1, ft_parse_assign(buf, vars)));
	return (ft_error_print(2, ft_parse_line_poly(buf, *vars)));
}
