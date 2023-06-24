/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:08:00 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/24 14:02:54 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTORV2_H
# define COMPUTORV2_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <math.h>
# include "get_next_line.h"

# define MAX_ITERATIONS	20

typedef struct s_cd
{
	double			real;
	double			imag;
}					t_cd;

/**
typedef struct s_poly
{
	char		*name;
	int			degree;
	t_cd		*coff;
}				t_poly;
*/

typedef struct s_poly_var
{
	double			degree;
	t_cd			coff;
}					t_poly_var;

typedef struct s_poly
{
	char			*var_name;
	double			min_degree;
	double			max_degree;
	uint8_t			contain_root;
	int				num_vars;
	t_list			*coff;
}					t_poly;

struct	s_var;

typedef struct s_matrix
{
	uint32_t		m;
	uint32_t		n;
	struct s_var	**matrix;
}					t_matrix;

typedef enum e_var_type
{
	CV2_NONE = 0,
	CV2_POLY = 1,
	CV2_MATRIX = 2,
	CV2_FUNC = 3,
	CV2_COMPLEX = 4,
	CV2_RATIONAL = 5,
	CV2_OP = 6
}					t_var_type;

typedef union u_vars
{
	t_matrix		matrix;
	t_poly			poly;
	char			ch;
}					t_vars;

typedef struct s_var
{
	char			*var_name;
	t_var_type		type;
	t_vars			choice;
}					t_var;

typedef struct s_poly_inp
{
	t_list			*vars_avail;
	t_var			out;
	char			*inp;
	char			*var_name;
	char			end_char;
}					t_poly_inp;

typedef struct s_poly_op
{
	t_list			*stack_vars;
	t_list			*stack_op;
	t_var_type		prev_type;
	t_poly_inp		*poly_inp;
}					t_poly_op;

void				ft_skipspaces(char **inp);
int					ft_valid(char ch);
int					ft_parse_inp_move(char **inp);
void				ft_parse_num(char **inp, double *coff, int8_t is_minus);
int					ft_parse_var(char **inp, t_list *vars, t_list **stack_vars);

int					ft_find_var_from_name(char *var_name, t_list *vars,
						t_var **new_v);
void				ft_var_free(t_var *var);
int					ft_var_op(t_var *out, t_var *v1, t_var *v2, char op);
int					ft_var_op_wo_free(t_var *out, t_var *v1,
						t_var *v2, char op);
int					ft_var_cpy_no_name(t_var *dst, t_var *src);
int					ft_var_num_init(t_var *v, double real, t_cd *coff);

double				ft_pow(double val, int n);
long				ft_gcd(long a, long b);
int					ft_newton(double val, uint16_t pow, double *out);
int					ft_gen_pow(double val, double pow, double *out);
void				ft_gen_frac(double num, long *numr, long *deno);

void				ft_cd_init(t_cd *out, double real, double imag);
int					ft_cd_scalar_mult(t_cd *out, double num, t_cd c);
int					ft_cd_add(t_cd *out, t_cd c1, t_cd c2, uint8_t sub);
int					ft_cd_mult(t_cd *out, t_cd c1, t_cd c2);
int					ft_cd_div(t_cd *out, t_cd c1, t_cd c2);
int					ft_cd_pow(t_cd *out, t_cd c, int pow);

void				ft_poly_init(t_poly *poly, double degree, char *name);
int					ft_poly_var_init(t_poly *poly, double degree, t_cd coff);
int					ft_poly_cpy(t_poly *dst, t_poly *src);
void				ft_poly_free(t_poly *poly);
int					ft_poly_add(t_poly *out, t_poly *p1,
						t_poly *p2, uint8_t sub);
int					ft_poly_mult(t_poly *out, t_poly *p1, t_poly *p2);
int					ft_poly_div(t_poly *out, t_poly *p1, t_poly *p2);
int					ft_poly_pow(t_poly *out, t_poly *p1, t_poly *p2);

int					ft_stack_push(t_list **stack, t_var *var);
int					ft_stack_pop(t_list **stack, t_var **var);
int					ft_stack_top(t_list *stack, t_var *var);
int					ft_stack_len(t_list *stack);
void				ft_stack_free(t_list **stack);

void				ft_matrix_free(t_matrix *matrix);
int					ft_matrix_init(t_matrix *matrix, uint32_t m, uint32_t n);
int					ft_matrix_add(t_matrix *out, t_matrix *m1,
						t_matrix *m2, uint8_t sub);
int					ft_matrix_scalar_mult(t_matrix *out,
						t_matrix *m1, t_var *v);
int					ft_matrix_mult(t_matrix *out, t_matrix *m1, t_matrix *m2);
int					ft_matrix_add_row(t_matrix *matrix);

void				ft_print_complex(t_cd *c, uint8_t in_poly,
						uint8_t is_first);
void				ft_print_poly(t_poly *poly);
void				ft_print_matrix(t_matrix *matrix);
void				ft_print_var(t_var *v, uint8_t nl);
void				ft_stack_print(t_list *v);

int					ft_parse_num_str(char **inp, double num,
						t_poly_op *poly_op);

int					ft_process_stack_op(t_poly_op *poly_op);
int					ft_empty_op_stack(t_poly_op *poly_op, uint8_t cbrac);
int					ft_add_op_stack(t_poly_op *poly_op, char op);
int					ft_parse_op_validate(char op, t_poly_op *poly_op);
int					ft_parse_op(char **inp, t_poly_op *poly_op);
int					ft_parse_poly(t_poly_inp *poly_inp);
int					ft_parse_var_name(char **inp, t_list *var_avail,
						t_poly_op *poly_op);
void				ft_parse_name(char **inp, char **var_name);
int					ft_process_line(char *buf, t_list **vars);
int					ft_parse_assign(char *buf, t_list **var);
int					ft_parse_poly_var(char **inp, t_poly_op *poly_op,
						char *var_name);
int					ft_parse_func_var(t_var *func, char **inp,
						t_poly_op *poly_op);
int					ft_parse_matrix(char **inp, t_poly_op *poly_op);
int					ft_parse_eqn(char *buf, t_list *vars);

int					ft_op_precedence(char op);

int					ft_process_func_op(t_var *out, t_var *func, t_var *arg);
int					ft_func_num_process(t_var *out, t_var *func, t_var *arg);
int					ft_func_poly_process(t_var *out, t_var *func, t_var *arg);

int					ft_solve_eqn(t_var *v);
void				ft_solve_quad(t_cd *coff, t_cd *des);
void				ft_solve_outlier(t_cd c);
void				ft_solve_linear(t_cd *coff);

void				ft_sigint_recv(int signo);
int					ft_error_print(int err_no, int ret);
#endif
