#include "computorv2.h"

void	ft_cd_init(t_cd *out, double real, double imag)
{
	if (!out)
		return ;
	out->real = real;
	out->imag = imag;
}

void	ft_cd_scalar_mult(t_cd *out, double num, t_cd c)
{
	if (!out)
		return ;
	out->real = num * c.real;
	out->imag = num * c.imag;
}

void	ft_cd_add(t_cd *out, t_cd c1, t_cd c2)
{
	if (!out)
		return ;
	out->real = c1.real + c2.real;
	out->imag = c2.imag + c2.imag;
}

void	ft_cd_sub(t_cd *out, t_cd c1, t_cd c2)
{
	if (!out)
		return ;
	out->real = c1.real - c2.real;
	out->imag = c2.imag - c2.imag;
}

void	ft_cd_mult(t_cd *out, t_cd c1, t_cd c2)
{
	if (!out)
		return ;
	out->real = (c1.real * c2.real) - (c1.imag * c2.imag);
	out->imag = (c1.real * c2.imag) + (c1.imag * c2.real);
}
