#include "computorv2.h"

static int	ft_poly_add_sub_single_var(t_poly *out, t_poly_var *pvar1,
				t_poly_var *pvar2, uint8_t sub)
{
	t_cd	c;

	if (!pvar1 || !pvar2 || !out)
		return (-1);
	if (pvar1 && pvar2 && pvar1->degree == pvar2->degree)
	{
		ft_cd_add(&c, pvar1->coff, pvar2->coff, sub);
		return (ft_poly_var_init(out, pvar1->degree, c));
	}
	if (pvar1 && ((pvar2 && pvar2->degree > pvar1->degree) || !pvar2)
		&& ft_poly_var_init(out, pvar1->degree, pvar1->coff) == -1)
		return (-1);
	if (pvar2 && ft_poly_var_init(out, pvar2->degree, pvar2->coff) == -1)
		return (-1);
	if (pvar1 && ft_poly_var_init(out, pvar1->degree, pvar1->coff) == -1)
		return (-1);
	return (0);
}

static int	ft_poly_add_sub_loop(t_poly *out, t_list *ele1, t_list *ele2, uint8_t sub)
{
	t_poly_var	*pvar1;
	t_poly_var	*pvar2;

	if (!out)
		return (-1);
	while (ele1 || ele2)
	{
		pvar1 = 0;
		pvar2 = 0;
		if (ele1)
			pvar1 = (t_poly_var *)(ele1->content);
		if (ele2)
			pvar2 = (t_poly_var *)(ele2->content);
		if (ft_poly_add_sub_single_var(out, pvar1, pvar2, sub) == -1)
			return (-1);
		if (ele1)
			ele1 = ele1->next;
		if (ele2)
			ele2 = ele2->next;
	}
	return (0);
}

int	ft_poly_add(t_poly *out, t_poly *p1, t_poly *p2, uint8_t sub)
{
	if (!out || !p1 || !p2)
		return (-1);
	ft_poly_init(out, 0, 0);
	if (ft_poly_add_sub_loop(out, p1->coff, p2->coff, sub) == -1)
	{
		ft_poly_free(out);
		return (-1);
	}
	return (0);
}