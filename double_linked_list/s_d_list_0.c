/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_d_list_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:10:09 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 16:45:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./double_linked_list.h"

t_d_list	*ft_d_lstnew(void *content)
{
	t_d_list	*ret;

	ret = (t_d_list *)malloc(sizeof(t_d_list));
	if (!ret)
		exit(15);
	ret->next = NULL;
	ret->prev = NULL;
	ret->content = content;
	return (ret);
}

void	ft_d_lstadd_front(t_d_list **lst, t_d_list *newnode)
{
	if (*lst)
	{
		newnode->next = *lst;
		newnode->prev = NULL;
		(*lst)->prev = newnode;
		*lst = newnode;
	}
	else
	{
		newnode->prev = NULL;
		*lst = newnode;
	}
}

int	ft_d_lstsize(t_d_list *lst)
{
	int			i;
	t_d_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_d_list	*ft_d_lstlast(t_d_list *lst)
{
	t_d_list	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_d_lstadd_back(t_d_list **lst, t_d_list *newnode)
{
	t_d_list	*last;

	if (!newnode)
		exit(15);
	if (*lst)
	{
		last = ft_d_lstlast(*lst);
		newnode->next = NULL;
		last->next = newnode;
		newnode->prev = last;
	}
	else
	{
		newnode->next = NULL;
		newnode->prev = NULL;
		*lst = newnode;
	}
}
