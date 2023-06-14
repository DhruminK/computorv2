#include "computorv2.h"

static int	ft_clean_poly(t_poly_op *poly_op, t_var *out, int ret)
{
	if (!poly_op)
		return (-1);
	if (!ret)
		ret = ft_empty_op_stack(poly_op, 0);
	if (!ret && (poly_op->stack_op || poly_op->stack_vars->next != 0))
		ret = -1;
	if (!ret)
		ret = ft_var_cpy_no_name(out,
				(t_var *)(poly_op->stack_vars->content));
	ft_stack_free(&(poly_op->stack_vars));
	ft_stack_free(&(poly_op->stack_op));
	return (ret);
}

static int	ft_parse_poly_line(char **inp, char *var_name,
				t_list *var_avail, t_poly_op *poly_op)
{
	int	ret;

	if (!inp || !poly_op)
		return (-1);
	ret = ft_valid(*(*inp));
	if (ret == 2)
		return (ft_parse_num_str(inp, 0, poly_op));
	if (ret == 3 || ret == 4 || ret == 5 || ret == 6
		|| ret == 8 || ret == 9 || ret == 10)
		return (ft_parse_op(inp, poly_op));
	if (var_name && strncmp(var_name, (*inp), strlen(var_name)))
		return (-1);
	if (ret == 1)
		return (ft_parse_var_name(inp, var_avail, poly_op));
	return (-1);
}

int	ft_parse_poly(t_poly_inp *poly_inp)
{
	int			ret;
	t_poly_op	poly_op;

	if (!poly_inp || !(poly_inp->inp))
		return (-1);
	memset(&poly_op, 0, sizeof(t_poly_op));
	ret = 0;
	while (poly_inp->inp && *(poly_inp->inp)
			&& *(poly_inp->inp) != poly_inp->end_char)
	{
		ft_skipspaces(&(poly_inp->inp));
		ret = ft_parse_poly_line(&(poly_inp->inp), poly_inp->var_name, poly_inp->vars_avail, &poly_op);
		if (ret == -1)
			break ;
	}
	if (!ret && *(poly_inp->inp) && (poly_inp->end_char))
		ret = ft_parse_poly_line(&(poly_inp->inp), poly_inp->var_name, poly_inp->vars_avail, &poly_op);
	return (ft_clean_poly(&poly_op, &(poly_inp->out), ret));

}
