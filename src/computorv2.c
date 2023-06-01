/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:13:12 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/01 16:03:42 by dkhatri          ###   ########.fr       */
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

int	main(void)
{
	char	*buf;
	t_list	*vars;
	int		ret;

	vars = 0;
	while (1)
	{
		buf = 0;
		printf("> ");
		fflush(stdout);
		ret = get_next_line(0, &buf);
		if (ret < 1)
			return (1);
		if (ft_process_line(buf, &vars) == -1)
			return (1);
		free(buf);
	}
	return (0);
}
