/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:40:13 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 07:46:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_LINKED_LIST_H
# define DOUBLE_LINKED_LIST_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_d_list
{
	void			*content;
	struct s_d_list	*next;
	struct s_d_list	*prev;
}				t_d_list;
void		del_content(void *content);
//!			s_d_list_0.c
t_d_list	*ft_d_lstnew(void *content);
void		ft_d_lstadd_front(t_d_list **lst, t_d_list *newnode);
int			ft_d_lstsize(t_d_list *lst);
t_d_list	*ft_d_lstlast(t_d_list *lst);
void		ft_d_lstadd_back(t_d_list **lst, t_d_list *newnode);
//!			s_d_list_1.c
void		ft_d_lstdelone(t_d_list *lst, void (*del)(void *));
void		ft_d_lstclear(t_d_list **lst, void (*del)(void *));
void		ft_d_lstiter(t_d_list *lst, void (*f)(void *));
void		ft_d_lstdelfront(t_d_list **lst, void (*del)(void *));
void		ft_d_lstiter_back(t_d_list *lst, void (*f)(void *));
void		ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode);
#endif
