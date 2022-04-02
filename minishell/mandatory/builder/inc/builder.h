/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:44 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/02 21:12:32 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# include "../../../libft/libft.h"
# include "../../../double_linked_list/double_linked_list.h"
# include "../../inc/structs.h"
# include "../../parsing/inc/parser.h"

typedef enum e_builder_type {
	B_CMD,
	B_AND,
	B_OR,
}	t_builder_type;


typedef struct	s_builder
{
	t_builder_type	type;
	t_cmd			*cmd;
	t_d_list		*left;
	t_d_list		*right;
}				t_builder;

t_d_list	*get_tree_builder(t_ast *ast);
t_d_list	*get_tree_builder_pipline(t_ast *ast);
t_d_list	*get_tree_builder_op(t_ast *ast);
t_builder	*get_tree_builder_list(t_ast *ast);
t_redir		*get_tree_builder_redir(t_ast *ast);
char		*get_tree_builder_id(t_ast *ast);
void		ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode);
void		print_builder(t_d_list *build);
void		print_builder_pipline(t_d_list *build);
void		print_builder_op(t_builder *build);


#endif