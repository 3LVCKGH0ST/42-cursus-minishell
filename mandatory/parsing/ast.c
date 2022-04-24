/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:22:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:21:23 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ast.h"

t_ast	*ast_init_ast(t_type_node type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->args = NULL;
	ast->redir = NULL;
	ast->children = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->child = NULL;
	ast->value = NULL;
	ast->type_token = 0;
	ast->fd = 0;
	ast->fd_error = 0;
	ast->fd_file_error = NULL;
	return (ast);
}
