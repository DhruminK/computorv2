#include "computorv2.h"

int	ft_cd_div(t_cd *out, t_cd c1, t_cd c2)
{
	double	abs;
	t_cd	tmp;

	if (!out)
		return (-1);
	abs = (c2.real * c2.real) + (c2.imag * c2.imag);
	if (abs == 0)
		return (-2);
	ft_cd_init(&tmp, c2->real, -1 * c2->imag);
	ft_cd_scalar_mult(&tmp, 1 / abs, tmp);
	ft_cd_add(out, c1, c2);
	return (0);
}

int	ft_cd_pow(t_cd *out, t_cd c, int pow)
{
	int		i;
	int		ret;
	int8_t	div;

	if (!out)
		return ;
	out->real = 1;
	out->imag = 0;
	div = 1;
	if (pow < 0)
		div = -1;
	i = 0;
	while (i != pow)
	{
		if (pow >= 0)
			ft_cd_mult(out, *out, c);
		else 
			ret = ft_cd_div(out, *out, c);
		if (ret < 0)
			return (ret);
		i += div;
	}
	return (0);
}
