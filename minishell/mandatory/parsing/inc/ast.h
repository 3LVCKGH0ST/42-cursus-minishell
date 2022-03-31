/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:07:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 13:28:53 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "../../../libft/libft.h"
# include "../../../double_linked_list/double_linked_list.h"
# include "./token.h"

typedef enum e_type_node {
	AST_LIST,
	AST_ARG,
	AST_REDIR,
	AST_ID,
	AST_TXT,
	AST_QOUTE,
	AST_PAREN,
	AST_PIPELINE,
	AST_OP
}	t_type_node;
typedef struct s_ast
{
	t_type_node		type;
	t_d_list		*args;
	t_d_list		*redir;
	t_d_list		*children;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;
	t_e_token		type_token;
}	t_ast;

t_ast	*init_ast(t_type_node type);
#endif
