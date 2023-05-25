#include "computorv2.h"

void	ft_var_matrix_free(t_matrix *matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = -1;
	while (++i < var->m)
		free(matrix->matrix[i]);
	free(matrix->matrix);
	memset(matrix, 0, sizeof(t_matrix));
}

void	ft_var_poly_free(t_poly *poly)
{
	if (!poly)
		return ;
	if (poly->name)
		free(poly->name);
	if (poly->coff)
		free(poly->coff);
	memset(poly, 0, sizeof(t_poly));
}

void	ft_var_free(t_var *var)
{
	if (!var)
		return (-1);
	if (var->var_name)
		free(var->var_name);
	if (var->var_type == CV2_POLY || var->var_type == CV2_FUNC)
		ft_var_poly_free(&(var->choice.poly));
	else if (var->var_type == CV2_MATRIX)
		ft_var_matrix_free(&(var->choice.matrix));
	memset(var, 0, sizeof(t_var));
}
