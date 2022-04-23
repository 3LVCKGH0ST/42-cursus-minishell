/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:30:04 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:24:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/print_tree.h"

void	print_tree(t_ast *ast)
{
	if (ast == NULL)
		return ;
	else if (ast->type == AST_ID)
		print_tree_id(ast);
	else if (ast->type == AST_REDIR)
		print_tree_redir(ast);
	else if (ast->type == AST_LIST)
		print_tree_list(ast);
	else if (ast->type == AST_PIPELINE)
		print_tree_pipline(ast);
	else if (ast->type == AST_OP)
		print_tree_op(ast);
}
