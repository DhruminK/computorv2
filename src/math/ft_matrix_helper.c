#include "computorv2.h"

void	ft_matrix_free(t_matrix *matrix)
{
	uint32_t	i;
	uint32_t	j;

	if (!matrix || !(matrix->n) || !(matrix->m) || !(matrix->matrix))
		return ;
	i = 0;
	while (i < matrix->m)
	{
		if (!(matrix->matrix[i]))
		{
			i += 1;
			continue ;
		}
		j = 0;
		while (j < matrix->n)
			ft_var_free(&((matrix->matrix)[i][j++]));
		memset((matrix->matrix)[i], 0, sizeof(t_var) * matrix->n);
		free((matrix->matrix)[i]);
		(matrix->matrix)[i] = 0;
		i += 1;

	}
	free(matrix->matrix);
	memset(matrix, 0, sizeof(t_matrix));
}

int	ft_matrix_init(t_matrix *matrix, uint32_t m, uint32_t n)
{
	uint32_t	i;
	int			ret;

	if (!matrix || !m || !n)
		return (-1);
	matrix->m = m;
	matrix->n = n;
	matrix->matrix = (t_var **)calloc(m, sizeof(t_var *));
	if (!(matrix->matrix))
		return (-1);
	i = 0;
	ret = 0;
	while (i < m && ret > -1)
	{
		(matrix->matrix)[i] = (t_var *)calloc(n, sizeof(t_var));
		if (!((matrix->matrix)[i]))
			ret = -1;
		i += 1;
	}
	if (ret < 0)
		ft_matrix_free(matrix);
	return (ret);
}

int	ft_matrix_add_row(t_matrix *matrix)
{
	t_var		**tmp;

	if (!matrix || !(matrix->n))
		return (-1);
	tmp = realloc(matrix->matrix, sizeof(t_var *) * (matrix->m + 1));
	if (!tmp)
		return (-1);
	matrix->m += 1;
	matrix->matrix = tmp;
	(matrix->matrix)[matrix->m - 1] = (t_var *)calloc(matrix->n,
			sizeof(t_var));
	if (!((matrix->matrix)[matrix->m - 1]))
		return (-1);
	return (0);
}
