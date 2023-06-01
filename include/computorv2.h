/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:08:00 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:35:15 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTORV2_H
# define COMPUTORV2_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

# define MAX_ITERATIONS	8

typedef struct s_cd
{
	double		real;
	double		imag;
}				t_cd;


typedef struct s_poly
{
	char		*name;
	int			degree;
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
	CV2_RATIONAL = 5,
	CV2_OP = 6
}				t_var_type;

typedef union u_vars
{
	t_matrix	matrix;
	t_poly		poly;
	char		ch;
}				t_vars;

typedef struct s_var
{
	char		*var_name;
	t_var_type	type;
	t_vars		choice;
}				t_var;

void			ft_skipspaces(char **inp);
int				ft_valid(char ch);
int				ft_parse_inp_move(char **inp);
void			ft_parse_num(char **inp, double *coff, int8_t is_minus);
int				ft_parse_var(char **inp, t_list *vars, t_list **stack_vars);

void			ft_var_free(t_var *var);
int				ft_var_op(t_var *out, t_var *v1, t_var *v2, char op);
int				ft_var_cpy_no_name(t_var *dst, t_var *src);

double			ft_newton_root(t_poly *p, t_poly *p_prime);
double			ft_rt(double num, int8_t pow);
double			ft_get_val_x(double x, t_poly *poly);
double			ft_pow(double val, int n);
double			ft_gen_pow(double val, double pow);
void			ft_frac(double n, long *numr, long *deno);

void			ft_cd_init(t_cd *out, double real, double imag);
int				ft_cd_scalar_mult(t_cd *out, double num, t_cd c);
int				ft_cd_add(t_cd *out, t_cd c1, t_cd c2, uint8_t sub);
int				ft_cd_mult(t_cd *out, t_cd c1, t_cd c2);
int				ft_cd_div(t_cd *out, t_cd c1, t_cd c2);
int				ft_cd_pow(t_cd *out, t_cd c, int pow);

int				ft_poly_init(t_poly *poly, int8_t degree, char *name);
int				ft_poly_cpy(t_poly *dst, t_poly *src);
void			ft_poly_free(t_poly *poly);
int				ft_poly_add(t_poly *out, t_poly *p1, t_poly *p2, uint8_t sub);
int				ft_poly_mult(t_poly *out, t_poly *p1, t_poly *p2);
int				ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2);
int				ft_poly_pow(t_poly *out, t_poly *p1, t_poly *p2);

int				ft_stack_push(t_list **stack, t_var *var);
int				ft_stack_pop(t_list **stack, t_var **var);
int				ft_stack_top(t_list *stack, t_var *var);
int				ft_stack_len(t_list *stack);
void			ft_stack_free(t_list **stack);

void			ft_matrix_free(t_matrix *matrix);
int				ft_matrix_init(t_matrix *matrix, uint32_t m, uint32_t n);
int				ft_matrix_add(t_matrix *out, t_matrix *m1, t_matrix *m2, uint8_t sub);
int				ft_matrix_scalar_mult(t_matrix *out, t_matrix *m1, double num);
int				ft_matrix_mult(t_matrix *out, t_matrix *m1, t_matrix *m2);

void			ft_print_complex(t_cd *c, uint8_t in_poly);
void			ft_print_poly(t_poly *poly);
void			ft_print_matrix(t_matrix *matrix);
void			ft_print_var(t_var *v);


int				ft_parse_num_str(char **inp, double num, t_list **stack_vars);

int				ft_process_stack(t_list **stack_vars, t_list **stack_op, uint8_t cbrac);
int				ft_process_stack_add(t_list **stack_vars, t_list **stack_op, char op);
int				ft_parse_poly(char **inp, t_list *vars, t_var *new_v);
int				ft_parse_var(char **inp, t_list *vars, t_list **stack_vars);

int				ft_op_precedence(char op);
#endif
