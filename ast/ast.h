/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:07:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/29 16:24:10 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../libft/libft.h"
# include "./DoubleLinkedList.h"
#include "./lexer.h"

typedef enum e_type_node {
	AST_LIST, // args and redirs : ls < abc > abc -la
	AST_ARG, // args : ls abc -la
	AST_REDIR, // <<, >>, <, >
	AST_ID, // abc"def"a abc abc'abc'a
	AST_TXT, // abc
	//AST_SQOUTE,	// "abc"
	//AST_DQOUTE,	// 'abc'
	AST_QOUTE,	// 'abc' "abc"
	AST_PAREN, // ( AST_LIST ) (AST_OP) (AST_PIPELINE)
	AST_PIPELINE, // AST_LIST | AST_LIST | AST_LIST ; AST_PAREN | AST_PAREN | AST_PAREN ;
	AST_OP, // || &&;  AST_PIPELINE OP AST_PAREN ; AST_PIPELINE OP AST_PIPELINE  
}	t_type_node;
typedef struct s_ast
{
	t_type_node	type;

	//! AST_LIST
	t_d_list	*args; //? AST_ID AST_QOUTE
	t_d_list	*redir; //? AST_REDIR
	
	//! AST_OP
	struct s_ast	*left; //AST_PIPELINE AST_PAREN AST_LIST
	struct s_ast	*right; //AST_PIPELINE AST_PAREN AST_LIST
	//! AST_REDIR  AST_TXT  AST_QOUTE AST_OP
	t_e_token 	type_token;
	//! AST_ID AST_TXT AST_QOUTE AST_REDIR
	char		*value;
	//! AST_ID AST_PIPELINE
	t_d_list	*children; //? AST_TXT  AST_QOUTE 
}	t_ast;

t_ast	*init_ast(t_type_node type);
#endif
