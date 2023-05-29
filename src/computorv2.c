/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computorv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:13:12 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/29 17:13:21 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		ret;
	char	*buf;

	ret = 1;
	(void)ac;
	(void)av;
	while (ret)
	{
		buf = 0;
		ret = get_next_line(0, &buf);
		printf("RET : %d\n", ret);
		if (ret == -1 || ret == 0)
			return (0);
		printf("BUFFER : %s\n", buf);
	}
	return (0);
}
