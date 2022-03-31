/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:22:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 08:59:16 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ast.h"

t_ast	*init_ast(t_type_node type)
{
	t_ast	*ast;

	if (!(ast = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	ast->type = type;
	ast->args = NULL;
	ast->redir = NULL;
	ast->children = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->value = NULL;
	ast->type_token = 0;
	return (ast);
}