#ifndef STACK_H
# define STACK_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

typedef enum e_stack_type
{
	STACK_OP = 0,
	STACK_NUMBER = 1,
	STACK_VAR = 2
}					t_stack_type;

typedef union u_stack_un
{
	double			num;
	char			ch;
	char			*var;
}					t_stack_un;

typedef struct s_stack
{
	t_stack_type	type;
	t_stack_un		choice;
}					t_stack;

int					ft_stack_push(t_list **head,
						t_stack_type type, void *inp);
int					ft_stack_pop(t_list **head, t_stack *top);
int					ft_stack_top(t_list *head, t_stack *top);

#endif
