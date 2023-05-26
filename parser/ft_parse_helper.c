/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:20:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/22 18:01:02 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_skipspaces(char **inp)
{
	char	*s;

	if (!inp || !*inp)
		return ;
	s = *inp;
	while (s && *s && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s += 1;
	*inp = s;
}

int	ft_valid(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	else if (ch >= 'a' && ch <= 'z')
		return (2);
	else if (ch >= '0' && ch <= '9')
		return (3);
	else if (ch == '+')
		return (4);
	else if (ch == '-')
		return (5);
	else if (ch == '*')
		return (6);
	else if (ch == '=')
		return (7);
	else if (ch == '^')
		return (8);
	else if (ch == '(')
		return (9);
	else if (ch == ')')
		return (10);
	return (0);
}

int	ft_parse_inp_move(char **inp)
{
	int	ret;

	if (!inp || !*inp)
		return (0);
	ft_skipspaces(inp);
	ret = ft_valid(*(*inp));
	if (ret != 1 && ret != 2 && ret != 3 && ret != 0 && ret != 5)
		(*inp) += 1;
	return (ret);
}

void	ft_parse_name(char **inp, char **var_name)
{
	char	*s;
	int		val;

	if (!inp || !var_name)
		return ;
	*var_name = 0;
	val = ft_valid(*(*inp));
	if (val != 1 || val != 2)
		return ;
	s = *inp;
	while (s && *s && (val == 1 || val == 2 || val == 3))
		val = ft_valid(*(s++));
	*var_name = strndup(*inp, s - (*inp) + 1);
	if (!(*var_name))
		return ;
	*inp = s;
}
