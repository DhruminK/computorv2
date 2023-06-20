/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_func_assign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:28:09 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 15:23:22 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_parse_assign_func_validate(char **buf, char **func_var_name)
{
	char	*s;
	int		ret;

	if (!buf || !func_var_name)
		return (-1);
	s = *buf;
	ret = ft_valid(*s);
	if (ret != 9)
		return (0);
	s += 1;
	ft_parse_name(&s, func_var_name);
	if (!func_var_name)
		return (-1);
	ret = ft_parse_inp_move(&s);
	if (ret != 10)
		return (-1);
	*buf = s + 1;
	return (1);
}

static int	ft_parse_assign_validate(char **buf, char **var_name,
				char **func_var_name)
{
	int	ret;

	if (!buf || !var_name)
		return (-1);
	ret = ft_parse_inp_move(buf);
	if (ret != 1)
		return (-1);
	ft_parse_name(buf, var_name);
	if (!(*var_name))
		return (-1);
	ret = ft_parse_assign_func_validate(buf, func_var_name);
	if (ret == -1)
		return (-1);
	if (ft_parse_inp_move(buf) != 7)
		return (-1);
	(*buf) += 1;
	ft_skipspaces(buf);
	return (0);
}

static void	ft_parse_assign_find_rm_old(t_list **vars, char *var_name)
{
	t_list	**head;
	t_list	*ele;
	t_var	*v;

	if (!vars || !var_name)
		return ;
	head = vars;
	while (*head)
	{
		v = (t_var *)((*head)->content);
		if (!strcasecmp(v->var_name, var_name))
			break ;
		head = &((*head)->next);
	}
	if (!(*head))
		return ;
	ele = ft_lstrm_front_ptr(head);
	if (!ele)
		return ;
	ft_var_free((t_var *)(ele->content));
	free(ele->content);
	free(ele);
}

static int	ft_parse_assign_add_var(t_list **vars,
				t_var *new_v, char *func_name)
{
	t_list	*ele;

	if (!vars || !new_v || !(new_v->var_name))
		return (-1);
	ft_parse_assign_find_rm_old(vars, new_v->var_name);
	if (new_v->type != CV2_MATRIX && new_v->choice.poly.var_name)
		free(new_v->choice.poly.var_name);
	if (new_v->type != CV2_MATRIX)
		new_v->choice.poly.var_name = func_name;
	if (func_name)
		new_v->type = CV2_FUNC;
	ele = ft_lstnew(new_v, sizeof(t_var));
	if (!ele)
	{
		ft_var_free(new_v);
		return (-1);
	}
	ft_lstadd_back(vars, ele);
	ft_print_var(new_v, 1);
	return (0);
}

int	ft_parse_assign(char *buf, t_list **var)
{
	char		*var_name;
	char		*func_name;
	t_poly_inp	poly_inp;

	if (!buf || !var)
		return (-1);
	var_name = 0;
	func_name = 0;
	if (ft_parse_assign_validate(&buf, &var_name, &func_name) == -1)
		return (-1);
	memset(&poly_inp, 0, sizeof(t_poly_inp));
	poly_inp.vars_avail = *var;
	poly_inp.inp = buf;
	poly_inp.var_name = func_name;
	if (ft_parse_poly(&poly_inp) == -1)
	{
		free(var_name);
		free(func_name);
		return (-1);
	}
	poly_inp.out.var_name = var_name;
	return (ft_parse_assign_add_var(var, &(poly_inp.out), func_name));
}
