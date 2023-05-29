/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:32:37 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:12:51 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_parse_var_name(char **inp, char **var_name)
{
	char	*s;
	int		ret;

	if (!inp || !var_name)
		return (-1);
	ret = ft_valid(*(*inp));
	if (ret != 1)
		return (0);
	s = *inp;
	while (s && *s && (ret == 1 || ret == 2))
		ret = ft_valid(*(++s));
	*var_name = strndup(*inp, s - *inp);
	if (!(*var_name))
		return (-1);
	*inp = s;
	return (1);
}

static void	ft_find_var(t_list *vars, t_list **nv, char *var_name)
{
	t_list	*ele;

	if (!var || !nv)
		return ;
	*nv = 0;
	ele = *vars;
	while (ele)
	{
		*nv = (t_var *)(ele->content);
		if (strcasecmp((*nv)->var_name, var_name) == 0)
			return ;
		ele = ele->next;
	}
	*nv = 0;
}

static int	ft_parse_init_out(t_var *v, t_var *out)
{
	if (!out)
		return (-1);
	if (!v)
		return (ft_var_poly_init(out, CV2_RATIONAL, 0, 0));
	if (v->type == CV2_COMPLEX || v->type == CV2_RATIONAL)
	{
		if (ft_var_poly_init(out, v->type, 0, 0) == -1)
			return (-1);
		memcpy(out->choice.poly.coff, v->choice.poly.coff,
			sizeof(t_cd) * out->choice.poly.degree);
		return (0);
	}
}

int	ft_parse_var(char **inp, t_list *vars, t_var *out)
{
	char	*var_name;
	t_var	*v;
	int		ret;

	if (!inp || !vars || !out)
		return (-1);
	*v = 0;
	ret = ft_parse_var_name(inp, &var_name);
	if (ret < 1)
		return (-1);
	ft_find_var(vars, &v, var_name);
	ret = ft_parse_init_out(v, out);
	free(var_name);
	return (ret);
}
