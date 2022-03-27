/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:07:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 12:28:25 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../libft/libft.h"
# include "./DoubleLinkedList.h"

typedef enum e_type_node {
	AST_LIST,
	AST_PAREN,
	AST_PIPELINE,
	AST_OP,
	AST_REDIR,
}	t_type_node;
typedef struct s_ast
{
	t_type_node	type;
	t_d_list	*children ;
	char		*value;
}	t_ast;

t_ast	*init_ast(t_type_node type);
#endif
