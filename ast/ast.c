/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:22:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/29 19:24:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*init_ast(t_type_node type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->type = type;
	
	ast->args = NULL;
	ast->redir = NULL;
	ast->children = NULL;
	ast->right = NULL;
	ast->left = NULL;
	ast->value = NULL;
	return (ast);
}
