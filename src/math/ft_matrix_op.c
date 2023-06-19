#include "computorv2.h"

static int	ft_matrix_validate(t_matrix *out, t_matrix *m1, t_matrix *m2, char op)
{
	if (!out || !m1 || !m2 || !(m1->matrix) || !(m2->matrix)
		|| !(m1->m) || !(m1->n) || !(m2->m) || !(m2->n))
		return (-1);
	if ((op == '+' || op == '-') && m1->m == m2->m && m1->n == m2->n)
		return (ft_matrix_init(out, m1->m, m1->n));
	if (op == 'm' && (m1->n == m2->m))
		return (ft_matrix_init(out, m1->m, m2->n));
	if (op == '*')
		return (ft_matrix_init(out, m1->m, m1->n));
	return (0);
}

int	ft_matrix_add(t_matrix *out, t_matrix *m1, t_matrix *m2, uint8_t sub)
{
	char		op;
	uint32_t	i;
	uint32_t	j;

	op = '+';
	if (sub)
		op = '-';
	if (ft_matrix_validate(out, m1, m2, op) == -1)
		return (-1);
	i = 0;
	while (i < out->m)
	{
		j = 0;
		while (j < out->n)
		{
			if (ft_var_op_wo_free(&(out->matrix[i][j]),
					&(m2->matrix[i][j]), &(m1->matrix[i][j]), op) == -1)
				return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}

static int	ft_matrix_mult_helper(t_matrix *out, t_matrix *m1, t_matrix *m2, uint32_t x[2])
{
	uint32_t	k;
	t_var		tmp1;
	t_var		tmp2;

	if (!out || !m1 || !m2)
		return (-1);
	k = 0;
	if (ft_var_num_init(&(out->matrix[x[0]][x[1]]), 0, 0) == -1)
		return (-1);
	while (k < m1->n)
	{
		if (ft_var_op_wo_free(&tmp1,
					&(m2->matrix[k][x[1]]), &(m1->matrix[x[0]][k]), '*') == -1)
			return (-1);
		if (ft_var_op(&tmp2, &(out->matrix[x[0]][x[1]]), &tmp1, '+') == -1)
			return (-1);
		memcpy(&(out->matrix[x[0]][x[1]]), &tmp2, sizeof(t_var));
		k += 1;
	}
	return (0);
}

int	ft_matrix_mult(t_matrix *out, t_matrix *m1, t_matrix *m2)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	x[2];

	if (ft_matrix_validate(out, m1, m2, 'm') == -1)
		return (-1);
	i = 0;
	while (i < out->m)
	{
		x[0] = i;
		j = 0;
		while (j < out->n)
		{
			x[1] = j;
			if (ft_matrix_mult_helper(out, m1, m2, x) == -1)
				return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}

int	ft_matrix_scalar_mult(t_matrix *out, t_matrix *m1, t_var *v)
{
	uint32_t	i;
	uint32_t	j;

	if (!v || ft_matrix_validate(out, m1, m1, '*') == -1)
		return (-1);
	i = 0;
	while (i < out->m)
	{
		j = 0;
		while (j < out->n)
		{
			if (ft_var_op_wo_free(&(out->matrix[i][j]),
					&(m1->matrix[i][j]), v, '*') == -1)
				return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}
