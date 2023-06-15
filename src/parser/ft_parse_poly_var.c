#include "computorv2.h"

static int	ft_parse_poly_find_degree(char **inp, double *degree)
{
	int	ret;

	if (!inp || !degree)
		return (-1);
	*degree = 1;
	ret = ft_parse_inp_move(inp);
	if (ret != 8)
		return (0);
	(*inp) += 1;
	*degree = 0.0;
	ft_parse_num(inp, degree, 0);
	return (0);
}

static int	ft_parse_poly_var_name_validate(char **inp, double *deg, char *var_name)
{
	int		ret;
	char	*s;

	if (!inp || !var_name || !deg)
		return (-1);
	s = (*inp) + strlen(var_name);
	ret = ft_valid(*s);
	if (ret == 1 || ret == 2)
		return (0);
	*inp = s;
	ret = ft_parse_poly_find_degree(inp, deg);
	if (ret == -1)
		return (-1);
	return (1);
}

int	ft_parse_poly_var(char **inp, t_poly_op *poly_op, char *var_name)
{
	double	deg;
	t_var	v;
	int		ret;
	t_cd	coff;

	if (!inp || !poly_op || !var_name)
		return (-1);
	ret = ft_parse_poly_var_name_validate(inp, &deg, var_name);
	if (ret < 1)
		return (ret);
	memset(&coff, 0, sizeof(t_cd));
	coff.real = 1;
	v.var_name = 0;
	v.type = CV2_POLY;
	ft_poly_init(&(v.choice.poly), 0, var_name);
	if (ft_poly_var_init(&(v.choice.poly), deg, coff) == -1)
		return (-1);
	ret = ft_stack_push(&(poly_op->stack_vars), &v);
	if (ret == -1)
	{
		ft_var_free(&v);
		return (-1);
	}
	return (1);
}
