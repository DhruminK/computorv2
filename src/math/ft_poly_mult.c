#include "computorv2.h"

static int	ft_poly_op_mult_loop(t_poly *out, t_list *ele1, t_list *ele2)
{
	t_poly_var	*p1;
	t_poly_var	*p2;
	t_cd		coff;

	if (!out || !ele1 || !ele2)
		return (-1);
	p1 = (t_poly_var *)(ele1->content);
	p2 = (t_poly_var *)(ele2->content);
	ft_cd_mult(&coff, p1->coff, p2->coff);
	return (ft_poly_var_init(out, p1->degree + p2->degree, coff));
}

int	ft_poly_mult(t_poly *out, t_poly *p1, t_poly *p2)
{
	t_list	*ele1;
	t_list	*ele2;

	if (!out || !p1 || !p2)
		return (-1);
	ft_poly_init(out, 0, 0);
	ele1 = p1->coff;
	while (ele1)
	{
		ele2 = p2->coff;
		while (ele2)
		{
			if (ft_poly_op_mult_loop(out, ele1, ele2) == -1)
				return (-1);
			ele2 = ele2->next;
		}
		ele1 = ele1->next;
	}
	return (0);
}

int	ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2)
{
	t_cd	coff;
	t_cd	c1;
	t_cd	c2;

	if (!out || !p1 || !p2)
		return (-1);
	ft_poly_init(out, 0, 0);
	if (p1->num_vars > 1 || p2->num_vars > 1
		|| p1->max_degree != p2->min_degree || p1->max_degree != 0
		|| p2->max_degree != p2->min_degree || p2->max_degree != 0)
		return (-1);
	memset(&c1, 0, sizeof(t_cd));
	memset(&c2, 0, sizeof(t_cd));
	if (p1->coff)
		memcpy(&c1, &(((t_poly_var *)(p1->coff->content))->coff), sizeof(t_cd));
	if (p2->coff)
		memcpy(&c2, &(((t_poly_var *)(p2->coff->content))->coff), sizeof(t_cd));
	if (ft_cd_div(&coff, c1, c2) == -1)
		return (-1);
	return (ft_poly_var_init(out, 0, coff));
}

int	ft_poly_pow(t_poly *out, t_poly *base, t_poly *pow)
{
	t_cd		c1;
	t_cd		c2;
	t_cd		coff;

	printf("HERE %d %d\n", base->num_vars, pow->num_vars);
	if (!out || !base || !pow || base->num_vars > 1 || pow->num_vars > 1
		|| base->max_degree != pow->min_degree || base->max_degree != 0
		|| pow->max_degree != pow->min_degree || pow->max_degree != 0)
		return (-1);
	printf("HERE\n");
	ft_poly_init(out, 0, 0);
	coff.imag = 0.0;
	memset(&c1, 0, sizeof(t_cd));
	memset(&c2, 0, sizeof(t_cd));
	if (base->coff)
		memcpy(&c1, &(((t_poly_var *)(base->coff->content))->coff), sizeof(t_cd));
	if (pow->coff)
		memcpy(&c2, &(((t_poly_var *)(pow->coff->content))->coff), sizeof(t_cd));
	ft_print_complex(&c2, 0);
	if (c2.imag != 0 || c1.real - (long)c1.real != 0)
		return (-1);
	if (c1.imag != 0 && ft_cd_pow(&coff, c1, (int)(c2.real)) == -1)
		return (-1);
	else if (c1.imag == 0.0 && ft_gen_pow(c1.real, c2.real, &(coff.real)) == -1)
		return (-1);
	return (ft_poly_var_init(out, 0, coff));
}
