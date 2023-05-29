#include "computorv2.h"

int	ft_stack_push(t_list **stack, t_stack_type type, void *ptr)
{
	t_stack	s;
	t_list	*ele;

	if (!stack || !ptr)
		return (-1);
	s.s_type = type;
	if (type == STACK_OP)
		s.vars.ch = *((char *)ptr);
	else if (type == STACK_NUM)
		s.vars.poly = (t_poly *)ptr;
	else
		s.vars.str = (char *)ptr;
	ele = ft_lstnew((void *)&s, sizeof(t_stack));
	if (!ele)
		return (-1);
	ft_lstadd_front(stack, ele);
	return (0);
}

int	ft_stack_pop(t_list **stack, t_stack **s)
{
	t_list	*ele;

	if (!stack || !s)
		return (-1);
	ele = ft_lstrm_front_ptr(stack);
	if (!ele)
		return (0);
	*s = (t_stack *)(ele->content);
	memset(ele, 0, sizeof(t_list));
	free(ele);
	return (1);
}

int	ft_stack_top(t_list *stack, t_stack *s)
{
	if (!s)
		return (-1);
	if (!stack)
		return (0);
	memcpy(s, stack->content, sizeof(t_stack));
	return (1);
}

int	ft_stack_len(t_list *stack)
{
	int	len;

	if (!stack)
		return (-1);
	len = 0;
	while (stack)
	{
		len += 1;
		stack = stack->next;
	}
	return (len);
}

void	ft_free_stack(t_list **stack)
{
	t_stack	*s;
	t_list	*ele;
	t_list	*next;

	if (!stack)
		return ;
	ele = *stack;
	while (ele)
	{
		s = (t_stack *)(ele->content);
		if (s && s->s_type == STACK_NUM && s->vars.poly)
		{
			ft_poly_free(s->vars.poly);
			free(s->vars.poly);
		}
		else if (s && s->stype == STACK_VAR)
			free(s->vars.str);
		if (s)
			free(s);
		next = ele->next;
		free(ele);
		ele = next;
	}
}
