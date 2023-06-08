/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:28 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/06 13:40:27 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_merge_two_buff(char **buf1, char *buf2, int buf2_len)
{
	int		len;
	int		nl_index;
	char	*buf1_cpy;

	if (!buf1)
		return (-1);
	if (!buf2 || !buf2_len)
		return (0);
	nl_index = -1;
	while (++nl_index < buf2_len)
	{
		if (buf2[nl_index] == '\n')
			break ;
	}
	len = 0;
	if (*buf1)
		len = strlen(*buf1);
	buf1_cpy = (char *)realloc(*buf1, sizeof(char) * (len + nl_index + 1));
	if (!buf1_cpy)
		return (-1);
	*buf1 = buf1_cpy;
	memcpy(*buf1 + len, buf2, nl_index * sizeof(char));
	(*buf1)[len + nl_index] = 0;
	return (nl_index);
}

static int	ft_read_line(t_fd_info *fd_info, char **buf)
{
	int		ret;
	int		index;
	char	buf2[BUFF_SIZE];

	if (!fd_info || !buf)
		return (-1);
	while (1)
	{
		ret = read(fd_info->fd, buf2, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		index = ft_merge_two_buff(buf, buf2, ret);
		if (index == -1 || index == ret - 1)
			return (index);
		if (index == ret && ret != BUFF_SIZE)
			return (0);
		if (index >= ret)
			continue ;
		fd_info->buf = strndup(buf2 + index + 1, ret - index);
		return (1);
	}
	return (0);
}

static int	ft_find_fd(const int fd, t_fd_info **fd_info, t_list **fds)
{
	t_list		*ele;
	t_fd_info	fdi;

	if (!fd_info || !fds)
		return (-1);
	ele = *fds;
	while (ele)
	{
		(*fd_info) = (t_fd_info *)(ele->content);
		if ((*fd_info)->fd == fd)
			return (1);
		ele = ele->next;
	}
	fdi.fd = fd;
	fdi.buf = 0;
	ele = ft_lstnew((void *)(&fdi), sizeof(t_fd_info));
	if (!ele)
		return (-1);
	ft_lstadd_back(fds, ele);
	*fd_info = (t_fd_info *)(ele->content);
	return (1);
}

int	get_next_line(const int fd, char **buf)
{
	static t_list	*fd_list = 0;
	t_fd_info		*fd_info;
	int				ret;

	if (!buf)
		return (-1);
	fd_info = 0;
	if (ft_find_fd(fd, &fd_info, &fd_list) == -1 || !fd_info)
		return (-1);
	*buf = fd_info->buf;
	fd_info->buf = 0;
	ret = ft_read_line(fd_info, buf);
	if (ret == -1 || ret == 0)
		return (0);
	return (1);
}
