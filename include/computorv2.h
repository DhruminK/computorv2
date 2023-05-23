/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:08:00 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/22 18:06:05 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTORV2_H
# define COMPUTORV2_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define MAX_ITERATIONS	8

typedef struct s_poly
{
	char		*name;
	int8_t		degree;
	double		*coff;
}				t_poly;

typedef struct s_matrix
{
	uint32_t	m;
	uint32_t	n;
	double		**matrix;
}				t_matrix;

typedef struct s_cd
{
	double		real;
	double		imag;
}				t_cd;

typedef enum e_var_type
{
	CV2_POLY = 0,
	CV2_MATRIX = 1,
	CV2_FUNC = 2,
	CV2_COMPLEX = 3,
	CV2_RATIONAL = 4
}				t_var_type;

typedef union u_vars
{
	t_cd		num;
	t_matrix	matirx;
	t_poly		poly;
}				t_vars;

typedef struct s_var
{
	char		*var_name;
	t_var_type	type;
	t_vars		choice;
}				t_var;


void			ft_skipspaces(char **inp);
void			ft_valid(char ch);
int				ft_parse_inp_move(char **inp);
void			ft_parse_num(char **inp, double *coff, int8_t is_minus);
#endif
