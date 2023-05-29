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
	{
		ret = ft_valid(*s);
		s += 1;
	}
	*var_name = strndup(*inp, s - *inp + 1);
	if (!(*var_name))
		return (-1);
	*inp = s;
	return (1);
}

static void	ft_find_var(t_list *vars, t_var **nv, char *var_name)
{
	t_list	*ele;

	if (!vars || !nv)
		return ;
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

int	ft_parse_var(char **inp, t_list *vars, t_poly *poly)
{
	char	*var_name;
	t_var	*v
	int		ret;

	if (!inp || !vars || !poly || !(poly->coff))
		return (-1);
	var_name = 0;
	ret = ft_parse_var_name(inp, &var_name);
	if (ret < 1)
		return (-1);
	ft_find_var(vars, &v, var_name);
	if (!v)
		memset(poly->coff, 0, sizeof(t_cd) * poly->degree);
	else
		memcpy(poly->coff, &(v->choice.poly.coff), sizeof(t_cd) * v->choice.poly.degree);
	free(var_name);
	return (0);
}
