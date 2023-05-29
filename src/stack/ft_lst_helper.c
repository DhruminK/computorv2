#include "get_next_line.h"

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list	*ele;

	ele = (t_list *)malloc(sizeof(t_list));
	if (!ele)
		return (0);
	ele->content = malloc(size);
	if (!(ele->content))
	{
		free(ele);
		return (0);
	}
	memcpy(ele->content, content, size);
	ele->size = size;
	ele->next = 0;
	return (ele);
}

void	ft_lstadd_front(t_list **head, t_list *ele)
{
	if (!head || !ele)
		return ;
	ele->next = *head;
	*head = ele;
}

void	ft_lstadd_back(t_list **head, t_list *ele)
{
	t_list	*e;

	if (!head || !ele)
		return ;
	if (!*head)
		return (ft_lstadd_front(head, ele));
	e = *head;
	while (e->next)
		e = e->next;
	e->next = ele;
}

t_list	*ft_lstrm_front_ptr(t_list **head)
{
	t_list	*ele;

	if (!head || !*head)
		return (0);
	ele = *head;
	*head = ele->next;
	return (ele);
}

t_list	*ft_lstrm_back_ptr(t_list **head)
{
	t_list	*ele;
	t_list	*prev;

	if (!head || !*head)
		return (0);
	if (!((*head)->next))
		return (ft_lstrm_front(head));
	ele = *head;
	prev = 0;
	while (ele->next)
	{
		prev = ele;
		ele = ele->next;
	}
	prev->next = 0;
	return (ele);
}
