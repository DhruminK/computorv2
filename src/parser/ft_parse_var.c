/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:34:38 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 12:34:39 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_find_var_from_name(char *var_name, t_list *vars, t_var **new_v)
{
	if (!var_name || !new_v)
		return (-1);
	*new_v = 0;
	while (vars)
	{
		*new_v = (t_var *)(vars->content);
		if (strcasecmp((*new_v)->var_name, var_name) == 0)
			return (1);
		vars = vars->next;
	}
	*new_v = 0;
	return (0);
}

static int	ft_var_name_process(char **var_name, t_poly_op *poly_op,
				t_list *var_avail, t_var **v)
{
	t_var	new_v;

	if (!var_name || !*var_name || !poly_op || !v
		|| ft_find_var_from_name(*var_name, var_avail, v) == -1)
		return (-1);
	if (!*v)
		return (ft_parse_num_str(0, 0, poly_op));
	if ((*v)->type == CV2_FUNC)
		return (1);
	if (ft_var_cpy_no_name(&new_v, *v) == -1)
		return (-1);
	new_v.var_name = *var_name;
	if (ft_stack_push(&(poly_op->stack_vars), &new_v) == -1)
		return (-1);
	poly_op->prev_type = new_v.type;
	*var_name = 0;
	return (0);
}

int	ft_parse_var_name(char **inp, t_list *var_avail, t_poly_op *poly_op)
{
	char	*var_name;
	int		ret;
	t_var	*v;

	if (!inp || !poly_op)
		return (-1);
	if (poly_op->prev_type != CV2_NONE && poly_op->prev_type != CV2_OP
		&& ft_add_op_stack(poly_op, '*') == -1)
		return (-1);
	ft_parse_name(inp, &var_name);
	if (!var_name)
		return (-1);
	ret = ft_var_name_process(&var_name, poly_op, var_avail, &v);
	/// TODO : processing of functions in case ret = 1
	if (var_name)
		free(var_name);
	if (ret == 0)
		return (0);
	return (-1);
}
