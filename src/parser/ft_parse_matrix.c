#include "computorv2.h"

static uint32_t	ft_parse_matrix_get_col_num(char *buf)
{
	uint32_t	num_cols;
	uint8_t		b;
	int			ret;

	if (!buf)
		return (0);
	num_cols = 0;
	b = 0;
	while (*buf && *buf != ']')
	{
		ret = ft_valid(*buf);
		if (!b && (ret == 1 || ret == 2))
			b = 1;
		if (*buf == ',')
			num_cols += 1;
		buf += 1;
	}
	if (b && num_cols != 0)
		num_cols += 1;
	return (num_cols);
}

static int	ft_parse_matrix_ele(char **inp, t_matrix *m,
				t_poly_inp *pi, uint32_t x[2])
{
	char	*csb;
	char	*com;
	int		ret;

	if (!inp || !m || !pi)
		return (-1);
	ret = 0;
	pi->end_char = ',';
	com = strchr(*inp, ',');
	csb = strchr(*inp, ']');
	if (!csb)
		return (-1);
	if (!com || (com && com > csb))
		pi->end_char = ']';
	memset(&(pi->out), 0, sizeof(t_var));
	pi->inp = *inp;
	if (ft_parse_poly(pi) == -1)
		ret = -1;
	memcpy(&(m->matrix[x[0]][x[1]]), &(pi->out), sizeof(t_var));
	*inp = (pi->inp + 1);
	if (!ret)
		return (0);
	ft_var_free(&(pi->out));
	return (-1);
}

static int	ft_parse_matrix_single_row(char **inp, t_matrix *m,
				uint8_t is_first, t_poly_inp *pi)
{
	uint32_t	i;
	int			ret;
	uint32_t	x[2];

	if (!inp || !m || !pi || (!is_first && ft_matrix_add_row(m) == -1))
		return (-1);
	ret = ft_parse_inp_move(inp);
	if (ret != 11)
		return (-1);
	(*inp) += 1;
	i = 0;
	x[0] = m->m - 1;
	while (i == 0 || (pi->end_char != ']'))
	{
		x[1] = i;
		if (i >= m->n)
			return (-1);
		if (ft_parse_matrix_ele(inp, m, pi, x) == -1)
			return (-1);
		i += 1;
	}
	return (0);
}

static int	ft_parse_matrix_rows(char **inp, t_matrix *m, t_poly_inp *pi)
{
	uint32_t	i;
	int			ret;

	if (!inp || !m || !pi)
		return (-1);
	i = 0;
	while (1)
	{
		if (ft_parse_matrix_single_row(inp, m, i == 0, pi) == -1)
			return (-1);
		ret = ft_parse_inp_move(inp);
		(*inp) += 1;
		i += 1;
		if (ret == 12)
			break ;
		if (ret == 13)
			continue ;
		return (-1);
	}
	return (0);
}

int	ft_parse_matrix(char **inp, t_poly_op *poly_op)
{
	t_var		v;
	t_poly_inp	pi;

	if (!inp || !poly_op || ft_parse_inp_move(inp) != 11)
		return (-1);
	(*inp) += 1;
	if (ft_parse_inp_move(inp) != 11)
		return (-1);
	if (ft_matrix_init(&(v.choice.matrix), 1,
		ft_parse_matrix_get_col_num(*inp + 1)) == -1)
		return (-1);
	pi.vars_avail = poly_op->poly_inp->vars_avail;
	pi.var_name = poly_op->poly_inp->var_name;
	if (ft_parse_matrix_rows(inp, &(v.choice.matrix), &pi) == -1)
		return (-1);
	v.type = CV2_MATRIX;
	v.var_name = 0;
	if (ft_stack_push(&(poly_op->stack_vars), &v) == -1)
		return (-1);
	return (0);
}
