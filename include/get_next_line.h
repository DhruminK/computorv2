/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:13 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/23 16:40:00 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define BUFF_SIZE 20

typedef struct s_list
{
	void			*content;
	size_t			size;
	struct s_list	*next;
}					t_list;

typedef struct s_fd_info
{
	int				fd;
	char			*buf;
}					t_fd_info;

void				ft_lstadd_back(t_list **head, t_list *ele);
void				ft_lstadd_front(t_list **head, t_list *ele);
t_list				*ft_lstnew(void const *content, size_t size);

int					get_next_line(const int fd, char **buf);

#endif
