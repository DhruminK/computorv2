#include "computorv2.h"

static int	ft_parse_assign_validate(char **buf, char **var_name)
{
	int	ret;

	if (!buf || !var_name)
		return (-1);
	*var_name = 0;
	ret = ft_parse_inp_move(buf);
	if (ret != 1)
		return (-1);
	ft_parse_name(buf, var_name);
	if (!*var_name)
		return (-1);
	ret = ft_parse_inp_move(buf);
	if (ret != 7)
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

static int	ft_parse_assign_add_var(t_list **vars, t_var *new_v)
{
	t_list	*ele;

	if (!vars || !new_v || !(new_v->var_name))
		return (-1);
	ft_parse_assign_find_rm_old(vars, new_v->var_name);
	ele = ft_lstnew(new_v, sizeof(t_var));
	if (!ele)
	{
		ft_var_free(new_v);
		return (-1);
	}
	ft_lstadd_back(vars, ele);
	ft_print_var(new_v);
	return (0);
}

int	ft_parse_assign(char *buf, t_list **var)
{
	char		*var_name;
	t_poly_inp	poly_inp;

	if (!buf || !var)
		return (-1);
	if (ft_parse_assign_validate(&buf, &var_name) == -1)
		return (-1);
	memset(&poly_inp, 0, sizeof(t_poly_inp));
	poly_inp.vars_avail = *var;
	poly_inp.inp = buf;
	if (ft_parse_poly(&poly_inp) == -1)
	{
		free(var_name);
		return (-1);
	}
	poly_inp.out.var_name = var_name;
	return (ft_parse_assign_add_var(var, &(poly_inp.out)));
}
