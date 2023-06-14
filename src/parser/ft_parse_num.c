/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:24:04 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 16:52:20 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static void	ft_parse_int(char **inp, double *coff)
{
	char	*s;

	*coff = 0;
	s = *inp;
	while (ft_valid(*s) == 2)
	{
		*coff = ((*coff) * 10) + (*s - '0');
		s += 1;
	}
	*inp = s;
}

static void	ft_parse_frac(char **inp, double *coff)
{
	char	*s;
	double	num;

	s = *inp;
	num = 0.1;
	while (ft_valid(*s) == 2)
	{
		*coff += ((*s - '0') * num);
		num *= 0.1;
		s += 1;
	}
	*inp = s;
}

void	ft_parse_num(char **inp, double *coff, int8_t is_minus)
{
	int		ret;

	if (!inp || !*inp || !coff)
		return ;
	ft_skipspaces(inp);
	ret = ft_valid(*(*inp));
	if (is_minus != 1 && is_minus != -1)
		is_minus = 1;
	if (ret == 5)
		is_minus *= -1;
	if (ret == 4 || ret == 5)
		(*inp) += 1;
	ft_parse_int(inp, coff);
	if (*(*inp) == '.')
	{
		(*inp) += 1;
		ft_parse_frac(inp, coff);
	}
	*coff *= is_minus;
}

int	ft_parse_num_str(char **inp, double num, t_list **stack_vars, t_var_type *vt)
{
	int		is_minus;
	t_cd	coff;
	t_var	var;

	if (!stack_vars || !vt)
		return (-1);
	var.type = CV2_RATIONAL;
	ft_poly_init(&(var.choice.poly), 0, 0);
	coff.imag = 0;
	coff.real = num;
	is_minus = 0;
	if (inp)
	{
		if (*(*inp) == '-')
			is_minus = 1;
		(*inp) += is_minus;
		ft_parse_num(inp, &(coff.real), is_minus);
	}
	if (ft_poly_var_init(&(var.choice.poly), 0, coff) == -1
		|| ft_stack_push(stack_vars, &var) == -1)
		is_minus = -1;
	*vt = var.type;
	if (is_minus == -1)
		ft_poly_free(&(var.choice.poly));
	return (is_minus);
}
