/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:30:04 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/07 00:54:05 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/print_tree.h"

void	free_tree(t_ast *ast)
{
	if (ast == NULL)
		return ;
	else if (ast->type == AST_ID)
		free_tree_id(ast);
	else if (ast->type == AST_REDIR)
		free_tree_redir(ast);
	else if (ast->type == AST_LIST)
		free_tree_list(ast);
	else if (ast->type == AST_PIPELINE)
		free_tree_pipline(ast);
	else if (ast->type == AST_OP)
		free_tree_op(ast);
}
