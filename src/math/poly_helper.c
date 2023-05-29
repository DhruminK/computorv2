#include "computorv2.h"

int	ft_poly_init(t_poly *poly, int8_t degree, char *name)
{
	if (!poly || degree < 0)
		return (-1);
	poly->name = 0;
	if (name)
	{
		poly->name = strdup(name);
		if (!(poly->name))
			return (-1);
	}
	poly->degree = 0;
	poly->coff = (t_cd *)calloc(poly->degree + 1, sizeof(t_cd));
	if (!poly->coff)
		return (-1);
	return (0);
}

void	ft_poly_free(t_poly *poly)
{
	if (!poly)
		return ;
	if (poly->name)
		free(poly->name);
	if (poly->coff)
		free(poly->coff);
	memset(poly, 0, sizeof(t_poly));
}

int	ft_poly_add(t_poly *out, t_poly *p1, t_poly *p2)
{
	int	i;

	if (!out || !p1 || !p2 || p1 == out || p2 == out)
		return (-1);
	memcpy(out, p1, sizeof(t_poly));
	if (out->degree < p2->degree)
		out->degree = p2->degree;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	memcpy(out->coff, p1->coff, sizeof(t_cd) * (p1->degree + 1));
	i = -1;
	while (++i <= p2->degree)
		ft_cd_add(out->coff + i, out->coff[i], p2->coff[i]);
	return (0);
}

int	ft_poly_sub(t_poly *out, t_poly *p1, t_poly *p2)
{
	int	i;

	if (!out || !p1 || !p2 || p1 == out || p2 == out)
		return (-1);
	memcpy(out, p1, sizeof(t_poly));
	if (out->degree < p2->degree)
		out->degree = p2->degree;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	memcpy(out->coff, p1->coff, sizeof(t_cd) * (p1->degree + 1));
	i = -1;
	while (++i <= p2->degree)
		ft_cd_sub(out->coff + i, out->coff[i], p2->coff[i]);
	return (0);
}

int	ft_poly_mult(t_poly *out, t_poly *p1, t_poly *p2)
{
	int		i;
	int		j;
	t_cd	c;

	if (!out || !p1 || !p2 || p1 == out || p2 == out)
		return (-1);
	out->degree = p1->degree + p2->degree;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	i = -1;
	while (++i <= p1->degree)
	{
		j = -1;
		while (++j <= p2->degree)
		{
			ft_cd_mult(&c, p1->coff[i], p2->coff[j]);
			ft_cd_add(out->coff + i + j, out->coff[i + j], c);
		}
	}
	return (0);
}

int	ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2)
{
	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 1 || p2->degree != 1)
		return (-1);
	out->degree = 0;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	if (ft_cd_div(out->coff, p1->coff[0], p2->coff[0]) == -1)
		return (-1);
	return (0);
}

int	ft_poly_pow(t_poly *out, t_poly *p1, t_poly *p2)
{
	if (!out || !p1 || !p2 || p1 == out || p2 == out
		|| p1->degree != 1 || p2->degree != 1
		|| p2->coff[0] - (int)p2->coff[0] != 0.0)
		return (-1);
	out->degree = 0;
	if (ft_poly_init(out, out->degree, 0) == -1)
		return (-1);
	if (ft_cd_pow(out->coff, p1->coff[0], (int)(p2->coff[0])) == -1)
		return (-1);
	return (0);
}
