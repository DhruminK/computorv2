/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_poly_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:36:03 by dkhatri           #+#    #+#             */
/*   Updated: 2023/06/17 12:36:04 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computorv2.h"

void	ft_poly_init(t_poly *poly, double degree, char *var_name)
{
	if (!poly)
		return ;
	memset(poly, 0, sizeof(t_poly));
	if (var_name)
	{
		poly->var_name = strdup(var_name);
		if (!(poly->var_name))
			return ;
	}
	if (degree < 0)
		poly->min_degree = degree;
	else
		poly->max_degree = degree;
	if (degree - ((long)degree) != 0.0)
		poly->contain_root = 1;
}

static int	ft_poly_var_find_coff(t_list **head, t_poly_var *p)
{
	t_poly_var	*pvar;
	uint8_t		b;
	t_list		*ele;

	if (!head || !p)
		return (-1);
	b = 0;
	while (*head)
	{
		pvar = (*head)->content;
		b = (pvar->degree == p->degree);
		if (pvar->degree <= p->degree)
			break ;
		head = &((*head)->next);
	}
	if (b == 1)
		return (ft_cd_add(&(pvar->coff), pvar->coff, p->coff, 0));
	ele = ft_lstnew(p, sizeof(t_poly_var));
	if (!ele)
		return (-1);
	ft_lstadd_front(head, ele);
	return (0);
}

int	ft_poly_var_init(t_poly *poly, double degree, t_cd coff)
{
	t_poly_var	p;

	if (!poly)
		return (-1);
	if (poly->max_degree < degree)
		poly->max_degree = degree;
	else if (poly->min_degree > degree)
		poly->min_degree = degree;
	if (degree - (long)degree != 0.0)
		poly->contain_root = 1;
	p.degree = degree;
	memcpy(&(p.coff), &coff, sizeof(t_cd));
	poly->num_vars += 1;
	return (ft_poly_var_find_coff(&(poly->coff), &p));
}

void	ft_poly_free(t_poly *poly)
{
	t_list	*ele;
	t_list	*next;

	ele = poly->coff;
	while (ele)
	{
		next = ele->next;
		memset(ele->content, 0, sizeof(t_poly_var));
		free(ele->content);
		free(ele);
		ele = next;
	}
	memset(poly, 0, sizeof(t_poly));
}

int	ft_poly_cpy(t_poly *dst, t_poly *src)
{
	t_poly_var	*pvar;
	t_list		*ele;
	int			ret;

	if (!dst || !src)
		return (-1);
	ft_poly_init(dst, 0, 0);
	ele = src->coff;
	while (ele)
	{
		pvar = (t_poly_var *)(ele->content);
		ret = ft_poly_var_init(dst, pvar->degree, pvar->coff);
		if (ret == -1)
			break ;
		ele = ele->next;
	}
	if (ret == 0)
		return (0);
	ft_poly_free(dst);
	return (-1);
}
