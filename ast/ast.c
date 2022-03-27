/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:22:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 12:21:50 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*init_ast(t_type_node type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->type = type;
	ast->children = NULL;
	ast->value = NULL;
	return (ast);
}
