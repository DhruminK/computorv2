#include "computorv2.h"

/**
static int	ft_process_line(char *buf, t_list *vars)
{
	t_poly_inp	inp;

	if (!buf)
		return (-1);
	memset(&inp, 0, sizeof(t_poly_inp));
	inp.vars_avail = vars;
	inp.inp = buf;
	inp.end_char = 0;
	if (ft_parse_poly(&inp) == -1)
		return (-1);
	ft_print_var(&(inp.out));
	ft_var_free(&(inp.out));
	return (0);
}
*/

static int	ft_get_line(t_list **vars)
{
	int		ret;
	char	*buf;

	buf = 0;
	printf("> ");
	fflush(stdout);
	ret = get_next_line(0, &buf);
	if (ret == 1 && strcasecmp("quit", buf) == 0)
		ret = 0;
	if (ret == 1 && ft_process_line(buf, vars) == -1)
		ret = -1;
	if (buf)
		free(buf);
	return (ret);
}

int	main(void)
{
	t_list	*vars;
	int		ret;

	vars = 0;
	ret = 0;
	signal(SIGINT, ft_sigint_recv);
	while (1)
	{
		ret = ft_get_line(&vars);
		if (ret < 1)
			break ;
	}
	if (ret < 0)
		return (1);
	printf("'quit' keyword or EOF detected, exiting the program\n");
	ft_stack_free(&vars);
	return (0);
}
