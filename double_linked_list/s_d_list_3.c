/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_d_list_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 07:45:49 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 07:46:32 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./double_linked_list.h"

/**
 * @brief will append a list to another list
 * 			 unlike ft_d_lstadd_back that add only one node
 * 
 * @param lst 
 * @param newnode list to append
 */
void	ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode)
{
	t_d_list	*last;

	if (!newnode)
		exit(15);
	if (*lst)
	{
		last = ft_d_lstlast(*lst);
		newnode->prev = last;
		last->next = newnode;
	}
	else
		*lst = newnode;
}
