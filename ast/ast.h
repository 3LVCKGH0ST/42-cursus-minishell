/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:07:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 10:18:45 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../libft/libft.h"

typedef enum e_type_ast_node {
	AST_LIST,
	AST_PAREN,
	AST_PIPELINE,
	AST_AND,
	AST_OR,
	AST_RIN,
	AST_ROUT,
	 
}	t_e_type_ast_node;


typedef struct s_ast
{
	size_t	i;
}	 t_ast;

#endif
