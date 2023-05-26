#include "computorv2.h"

static int	ft_solve_func_num(t_poly *poly, t_cd inp, t_cd *out)
{
	int		i;
	int		ret;
	t_cd	coff;

	i = -1;
	while (++i < poly->neg_degree)
	{
		ft_cd_pow(&coff, inp, (i - 1) * -1);
		ret = ft_cd_div(&coff, coff, poly->neg_coff[i]);
		if (ret < 0)
			return (ret);
		ft_cd_add(out, *out, coff);
	}
	i = -1;
	while (++i < poly->degree)
	{
		ft_cd_pow(&coff, inp, i);
		ft_cd_mult(&coff, coff, poly->coff[i]);
		ft_cd_add(out, *out, coff);
	}
	return (0);
}

static int	ft_solve_func_var(t_poly *poly, t_poly *out)
{
	int		i;
	t_cd	coff;

	if (!poly || !out)
		return (-1);
	i = -1;
	while (++i < poly->neg_degree)
		ft_cd_add(out->neg_coff + i,
				out->neg_coff[i], poly->neg_coff[i]);
	i = -1;
	while (++i < poly->degree)
		ft_cd_add(out->coff + i,
				out->coff[i], poly->coff[i]);
	return (0);
}

int	ft_func_realloc_degree(t_poly *poly, t_poly *out)
{
	t_cd	*tmp;

	if (!poly || !out)
		return (-1);
	if (poly->degree > out->degree)
	{
		tmp = (t_cd *)(realloc(out->coff, sizeof(t_cd) * poly->degree));
		if (!tmp)
			return (-1);
		memcpy(out->coff + out->degree,
				0, sizeof(t_cd) * (poly->degree - out->degree));
		out->degree = poly->degree;
	}
	if (poly->neg_degree > out->neg_degree)
	{
		tmp = (t_cd *)(realloc(out->coff, sizeof(t_cd) * poly->neg_degree));
		if (!tmp)
			return (-1);
		memcpy(out->coff + out->neg_degree,
				0, sizeof(t_cd) * (poly->neg_degree - out->neg_degree));
		out->neg_degree = poly->neg_degree;
	}
	return (0);
}

int	ft_solve_func(t_var *var, t_cd inp, t_poly *out, uint8_t is_num)
{
	t_poly	*poly;
	t_cd	*tmp;

	if (!var || !out)
		return (-1);
	if (var->type != CV2_FUNC || var->type != CV2_POLY)
		return (0);
	poly = &(var->choice.poly);
	if (ft_func_realloc_degree(poly, out) == -1)
		return (-1);
	if (is_num)
		return (ft_solve_func_num(poly, inp, out->coff));
	return (ft_solve_func_var(poly, out));
}
