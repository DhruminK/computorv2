#include "parser.h"

static int	ft_parse_operators(char **inp, t_list **op, int ret)
{
	int		b;
	char	ch;

	if (ret == 6 && *((*inp) + 1) == '*')
	{
		b = 2;
		ch = 'M';
	}
	else if (ret == 4 || ret == 5 || ret == 6
				|| ret == 8 || ret == 9 || ret == 10)
	{
		b = 1;
		ch = *(*inp);
	}
	if (b == 0)
		return (0);
	(*inp) += b;
	if (ft_stack_push(op, STACK_OP, (void *)&ch) == -1)
		return (-1);
	return (1);
}

static int	ft_parse_var_name(char **inp, t_list **vars, int val)
{
	char	*s;
	char	*str;

	if (ret != 1 && ret != 3)
		return (0);
	s = *inp - 1;
	val = 1;
	while (++s && (val == 1 || val == 2 || val == 9 || val == 10))
		val = ft_valid(*s);
	str = strndup(*inp, (s - (*inp) + 1));
	if (!str)
		return (-1);
	if (ft_stack_push(vars, STACK_VAR, (void *)str) == -1)
		return (-1);
	free(str);
	*inp = s;
	return (1);
}

static int	ft_parse_var_num(char **inp, t_list **vars)
{
	double	num;

	if (ret == 3)
		return (0);
	ft_parse_num(inp, &num, 0);
	if (ft_stack_push(vars, STACK_NUMBER, (void *)&num) == -1)
		return (-1);
	return (1);
}

int	ft_parse_poly(char **inp, t_list **op, t_list **vars)
{
	int	val;
	int	ret;

	if (!inp || !op || !var)
		return (-1);
	while (*(*inp))
	{
		ft_skipspaces(inp);
		val = ft_valid(*(*inp));
		ret = ft_search_operators(inp, op, val);
		if (!ret)
			ret = ft_parse_var_name(inp, vars, val);
		if (!ret && val == 3)
			ret = ft_parse_var_num(inp, vars);
		if (ret == -1 || ret == 0)
			return (-1);
	}
	return (0);
}
