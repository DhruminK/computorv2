/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:50:02 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/06 13:54:31 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_sigint_recv(int signo)
{
	printf("\nRecieved signal %d,\n", signo);
	printf("Please type 'quit' to exit\n");
	printf("Or use Ctrl + D to send an EOF to exit\n");
	printf("> ");
	fflush(stdout);
}
