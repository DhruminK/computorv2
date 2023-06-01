#include "computorv2.h"

void	ft_print_complex(t_cd *c, uint8_t in_poly)
{
	int		mult;

	if (!c)
		return ;
	mult = 1;
	if (c->real < 0.0 && in_poly)
	{
		printf(" - ");
		mult = -1;
	}
	else if (in_poly)
		printf(" + ");
	if (in_poly && c->imag != 0.0)
		printf("(");
	printf("%0.3f", mult * c->real);
	if (c->imag * mult < 0.0)
		printf("- %0.3f", c->imag);
	else
		printf("+ %0.3f", c->imag * mult);
	if (in_poly && c->imag != 0.0)
		printf(")");
}

void	ft_print_poly(t_poly *poly)
{
	int	i;

	if (!poly || poly->degree < 0 || !(poly->coff))
		return ;
	ft_print_complex(poly->coff, 0);
	i = 0;
	while (++i <= poly->degree)
	{
		ft_print_complex(poly->coff + i, 1);
		printf("x ^ %d", i);
	}
}

void	ft_print_matrix(t_matrix *matrix)
{
	uint32_t	i;
	uint32_t	j;

	if (!matrix || !(matrix->matrix))
		return ;
	i = 0;
	while (i < matrix->m)
	{
		j = 0;
		printf("[");
		while (j < matrix->n)
		{
			ft_print_complex(matrix->matrix[i] + j++, 0);
			printf(" , ");
		}
		printf("]\n");
		i += 1;
	}
}

void	ft_print_var(t_var *v)
{
	if (!v)
		return ;
	if (v->type == CV2_MATRIX)
		return (ft_print_matrix(&(v->choice.matrix)));
	else if (v->type == CV2_RATIONAL || v->type == CV2_COMPLEX)
		return (ft_print_complex(v->choice.poly.coff, 0));
	else if (v->type == CV2_OP || v->type == CV2_NONE)
		printf("This should not be printed\n");
	else
		return (ft_print_poly(&(v->choice.poly)));
}
