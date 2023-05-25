#include "stack.h"

int	ft_stack_push(t_list **head, t_stack_type type, void *inp)
{
	t_stack	stack;
	t_list	*ele;

	if (!head || !inp)
		return (-1);
	stack.type = type;
	if (type == STACK_NUMBER)
		stack.choice.num = *((double *)(inp));
	else if (type == STACK_OP)
		stack.choice.ch = *((char *)(inp));
	else if (type == STACK_VAR)
		stack.choice.var = strdup((char *)(inp));
	ele = ft_lstnew(&stack, sizeof(t_stack));
	if (!ele)
		return (-1);
	ft_lstadd_front(head, ele);
	return (0);
}

int	ft_stack_pop(t_list **head, t_stack *top)
{
	t_list	*ele;

	if (!head || !top)
		return (-1);
	if (!*head)
		return (0);
	ele = *head;
	(*head) = (*head)->next;
	memcpy(top, ele->content, sizeof(t_stack));
	free(ele->content);
	memset(ele, 0, sizeof(t_list));
	free(ele);
	return (1);
}

int	ft_stack_top(t_list *head, t_stack *top)
{
	t_list	*ele;

	if (!top)
		return (-1);
	if (!head)
		return (0);
	memcpy(top, head->content, sizeof(t_stack));
	return (1);
}
