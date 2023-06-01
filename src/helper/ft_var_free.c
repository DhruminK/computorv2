#include "computorv2.h"

void	ft_var_free(t_var *v)
{
	if (!v)
		return ;
	if (v->type == CV2_MATRIX)
		ft_matrix_free(&(v->choice.matrix));
	else if (v->type != CV2_NONE && v->type != CV2_OP)
		ft_poly_free(&(v->choice.poly));
	memset(v, 0, sizeof(t_var));
}

int	ft_op_precedence(char op)
{
	if (op == '+' || op == '-')
		return (1);
	else if (op == '*' || op == '/' || op == 'm' || op == 'M')
		return (2);
	else if (op == '^')
		return (3);
	return (0);
}
