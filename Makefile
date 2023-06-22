CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = computorv2

PARSER_PATH = parser/
MATH_PATH = math/
PRINT_PATH = print/
STACK_PATH = stack/
HELPER_PATH = helper/
FUNC_PATH = func/

HELPER = ft_var_free.c ft_var_op.c
MATH = complex_helper.c ft_newton.c ft_var_helper.c math_helper.c \
	   ft_matrix_helper.c ft_matrix_op.c ft_helper_func.c \
	   ft_poly_helper.c ft_poly_add.c ft_poly_mult.c \
	   ft_gen_frac.c ft_solve_eqn.c ft_solve_eqn_helper.c
PARSER = ft_parse_helper.c ft_parse_num.c ft_parse_op.c ft_parse_poly.c \
		 ft_parse_var.c ft_parse_func_assign.c ft_parse_line.c \
		 ft_parse_poly_var.c ft_parse_func.c ft_parse_matrix.c ft_parse_eqn.c
PRINT = ft_print_helper.c ft_print_stack.c
STACK = ft_lst_helper.c ft_stack_helper.c
FUNC = ft_func_math.c ft_func_num_process.c ft_func_poly_process.c

MAIN = computorv2.c get_next_line.c signal.c

SRC = $(MAIN)									\
	  $(addprefix $(PARSER_PATH), $(PARSER))	\
	  $(addprefix $(MATH_PATH), $(MATH))		\
	  $(addprefix $(PRINT_PATH), $(PRINT))		\
	  $(addprefix $(STACK_PATH), $(STACK))		\
	  $(addprefix $(FUNC_PATH), $(FUNC))		\
	  $(addprefix $(HELPER_PATH), $(HELPER))

OBJ = $(SRC:.c=.o)

INC = computorv2.h get_next_line.h
INCLUDES = -I include/

SRC_PATH = src/
INC_PATH = include/
OBJ_PATH = obj/
OBJS_PATH = $(addprefix $(OBJ_PATH), $(PARSER_PATH))	\
			$(addprefix $(OBJ_PATH), $(MATH_PATH))		\
			$(addprefix $(OBJ_PATH), $(PRINT_PATH))		\
			$(addprefix $(OBJ_PATH), $(STACK_PATH))		\
			$(addprefix $(OBJ_PATH), $(FUNC_PATH))		\
			$(addprefix $(OBJ_PATH), $(HELPER_PATH))

OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
SRCS = $(addprefix $(SRC_PATH), $(SRC))
INCS = $(addprefix $(INC_PATH), $(INC))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<
	@echo "\033[1m$(NAME)\033[0m \
		: Compiling $< to $@ \033[1;32m[OK]\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1m$(NAME)\033[0m \
		: Compiling $@ \033[1;32m[OK]\033[0m"

clean:
	@/bin/rm -f $(OBJS)
	@echo "\033[1m$(NAME)\033[0m \
		: Cleaned $(OBJ_PATH) \033[1;32m[OK]\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(OBJS_PATH) $(OBJ_PATH)
	@echo "\033[1m$(NAME)\033[0m \
		: binary deleted \033[1;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re
