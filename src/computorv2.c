/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:13:12 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/06 13:52:58 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

static int	ft_process_line(char *buf, t_list **vars)
{
	t_var	v;
	char	*inp;

	if (!buf)
		return (-1);
	memset(&v, 0, sizeof(t_var));
	inp = buf;
	if (ft_parse_poly(&inp, *vars, &v) == -1)
		return (-1);
	ft_print_var(&v);
	ft_var_free(&v);
	return (0);
}

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
	return (0);
}
