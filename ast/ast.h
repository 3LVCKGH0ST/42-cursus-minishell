/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:07:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/28 13:59:20 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../libft/libft.h"
# include "./DoubleLinkedList.h"

typedef enum e_type_node {
	AST_LIST,
	AST_REDIR,
	AST_ID,
	AST_TXT,
	AST_SQOUTE,
	AST_DQOUTE,
	AST_PAREN,
	AST_PIPELINE,
	AST_AND,
	AST_OR,
}	t_type_node;
typedef struct s_ast
{
	t_type_node	type;
	
	t_d_list	*children; //ast_list
	
	t_e_token 	type_token;
	char		*value;
	
}	t_ast;

t_ast	*init_ast(t_type_node type);
#endif
