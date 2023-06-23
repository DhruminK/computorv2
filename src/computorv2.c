/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:24:49 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/23 20:49:32 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

int	ft_error_print(int err_no, int ret)
{
	if (err_no == -2)
		printf("Error while calculation, "
			"cannot find root of irrational power\n");
	else if (err_no == 1)
		printf("Error while parsing assignment operation\n");
	else if (err_no == 2)
		printf("Error while parsing polynomial operation\n");
	else if (err_no == 3)
		printf("Error while parsing polynomial equation solution\n");
	return (ret);
}

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
		if (ret == 0)
			break ;
	}
	if (ret < 0)
		return (1);
	printf("'quit' keyword or EOF detected, exiting the program\n");
	ft_stack_free(&vars);
	return (0);
}
