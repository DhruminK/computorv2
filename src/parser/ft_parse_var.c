#include "computorv2.h"

static int	ft_process_var_name(char **inp, char **var_name)
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

static void	ft_find_var(t_list *vars, t_var **nv, char *var_name)
{
	if (!vars || !nv || !var_name)
		return ;
	*nv = 0;
	while (vars)
	{
		*nv = (t_var *)(vars->content);
		if (strcasecmp((*nv)->var_name, var_name) == 0)
			return ;
		vars = vars->next;
	}
	*nv = 0;
}

static int	ft_push_var_to_stack(t_list **stack_vars, t_var *var, uint8_t i)
{
	t_var	v;

	if (!stack_vars)
		return (-1);
	v.type = CV2_RATIONAL;
	if (i)
		v.type = CV2_COMPLEX;
	if ((i || !var) && ft_poly_init(&(v.choice.poly), 0, 0) == -1)
		return (-1);
	if (var && ft_var_cpy_no_name(&v, var) == -1)
		return (-1);
	if (ft_stack_push(stack_vars, &v) == 0)
		return (0);
	ft_var_free(&v);
	return (-1);
}

int	ft_parse_var(char **inp, t_list *vars, t_list **stack_vars)
{
	int		ret;
	uint8_t	i;
	t_var	*v1;
	char	*var_name;

	if (!inp || !vars || !stack_vars)
		return (-1);
	ret = ft_process_var_name(inp, &(var_name));
	if (ret < 1)
		return (-1);
	i = 0;
	v1 = 0;
	if (strcasecmp(var_name, "i") == 0)
		i = 1;
	if (!i)
		ft_find_var(vars, &v1, var_name);
	ret = ft_push_var_to_stack(stack_vars, v1, i);
	if (var_name)
		free(var_name);
	return (0);
}
