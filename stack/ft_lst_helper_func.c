/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_helper_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:55:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/05/23 17:01:16 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back(t_list **head, t_list *ele)
{
	t_list	*e;

	if (!head || !ele)
		return ;
	if (!*head)
	{
		*head = ele;
		return ;
	}
	e = *head;
	while (e->next)
		e = e->next;
	e->next = ele;
}

void	ft_lstadd_front(t_list **head, t_list *ele)
{
	if (!head || !ele)
		return ;
	ele->next = *head;
	*head = ele;
}

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list	*ele;

	if (!content || !size)
		return (0);
	ele = malloc(sizeof(t_list));
	if (!ele)
		return (0);
	ele->content = malloc(size);
	if (!(ele->content))
	{
		free(ele);
		return (0);
	}
	memcpy(ele->content, content, sizeof(size));
	ele->size = size;
	ele->next = 0;
	return (ele);
}
