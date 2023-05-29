/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:24:04 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 16:46:24 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static void	ft_parse_int(char **inp, double *coff)
{
	char	*s;

	*coff = 0;
	s = *inp;
	while (ft_valid(*s) == 3)
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
	while (ft_valid(*s) == 3)
	{
		*coff += ((*s - 0) / num);
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

int	ft_parse_num_str(char **inp, t_var *var)
{
	int	ret;
	int	is_minus;

	if (!inp || !var || ft_poly_init(&(var->choice.poly), 0, 0) == -1)
		return (-1);
	is_minus = 0;
	if (*(*inp) == '-')
	{
		is_minus = 1;
		(*inp) += 1;
	}
	var->type = CV2_RATIONAL;
	ft_parse_num(inp, &(var->choice.poly.coff->real), is_minus);
	return (0);
}
