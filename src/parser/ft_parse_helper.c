/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:32:51 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 16:33:05 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_skipspaces(char **inp)
{
	char	*s;

	if (!inp)
		return ;
	s = *inp;
	while (s && *s && (*s == ' '
			|| (*s >= 9 && *s <= 13)))
		s += 1;
	*inp = s;
}

int	ft_valid(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	else if (ch >= '0' && ch <= '9')
		return (2);
	else if (ch == '+')
		return (3);
	else if (ch == '-')
		return (4);
	else if (ch == '*')
		return (5);
	else if (ch == '/')
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
	if (val != 1)
		return ;
	s = *inp;
	while (s && *s && (val == 1 || val == 2))
		val = ft_valid(*(s++));
	*var_name = strndup(*inp, s - (*inp) + 1);
	if (!(*var_name))
		return ;
	*inp = s;
}

int	ft_parse_op_validate(char op, t_poly_op *poly_op)
{
	int	ret;

	if (!poly_op)
		return (-1);
	if (op == '-' && (poly_op->prev_type == CV2_OP
		|| poly_op->prev_type == CV2_NONE))
	{
		ret = ft_parse_num_str(0, -1, &(poly_op->stack_vars));
		if (ret == 0)
			ret = ft_add_op_stack(poly_op, '*');
		if (ret == -1)
			return (-1);
		return (1);
	}
	if (op == '(' && poly_op->prev_type != CV2_NONE
		&& poly_op->prev_type != CV2_OP)
		return (ft_add_op_stack(poly_op, '*'));
	return (0);
}
