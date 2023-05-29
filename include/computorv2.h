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
# include "get_next_line.h"
# include "stack.h"

# define MAX_ITERATIONS	8

typedef struct s_cd
{
	double		real;
	double		imag;
}				t_cd;


typedef struct s_poly
{
	char		*name;
	int8_t		degree;
	t_cd		*coff;
}				t_poly;

typedef struct s_matrix
{
	uint32_t	m;
	uint32_t	n;
	t_cd		**matrix;
}				t_matrix;

typedef enum e_var_type
{
	CV2_NONE = 0,
	CV2_POLY = 1,
	CV2_MATRIX = 2,
	CV2_FUNC = 3,
	CV2_COMPLEX = 4,
	CV2_RATIONAL = 5
}				t_var_type;

typedef union u_vars
{
	t_matrix	matirx;
	t_poly		poly;
}				t_vars;

typedef struct s_var
{
	char		*var_name;
	t_var_type	type;
	t_vars		choice;
}				t_var;

/********* STACK VARIABLES ************/
typedef enum e_stack_type
{
	STACK_OP = 0,
	STACK_NUM = 1,
	STACK_VAR = 2
}					t_stack_type;

typedef union u_stack_vars
{
	char			ch;
	t_poly			*poly;
	char			*str;
}					t_stack_vars;

typedef struct s_stack
{
	t_stack_type	s_type;
	t_stack_vars	vars;
}					t_stack;

void			ft_skipspaces(char **inp);
int				ft_valid(char ch);
int				ft_parse_inp_move(char **inp);
void			ft_parse_num(char **inp, double *coff, int8_t is_minus);

void			ft_cd_init(t_cd *out, double real, double imag);
void			ft_cd_scalar_mult(t_cd *out, double num, t_cd c);
void			ft_cd_add(t_cd *out, t_cd c1, t_cd c2);
void			ft_cd_sub(t_cd *out, t_cd c1, t_cd c2);
void			ft_cd_mult(t_cd *out, t_cd c1, t_cd c2);
int				ft_cd_div(t_cd *out, t_cd c1, t_cd c2);
int				ft_cd_pow(t_cd *out, t_cd c, int pow);

int				ft_find_realloc_degree(t_poly *poly, t_poly *out);
int				ft_solve_func(t_var *var, t_cd inp,
					t_poly *out, uint8_t is_num);

int				ft_perform_op(double *out, double num1, double num2, char op);
int				ft_process_var_stack(t_list **var, char op);

int				ft_op_precedence(char op);
int				ft_process_new_op(t_list **vars, t_list **ops, char op);

int				ft_process_op(t_list **vars, t_list **ops, uint8_t cbrac);
int				ft_parse_op(t_list **vars, t_list **ops, char ch);

int				ft_parse_assign(char **inp, char *var_name, t_poly *poly);
#endif
