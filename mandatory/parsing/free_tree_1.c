/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:30:04 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/02 22:58:30 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/print_tree.h"

void	free_tree_id(t_ast *ast)
{
	free(ast->value);
	free(ast);
}

void	free_tree_redir(t_ast *ast)
{
	if (ast->fd > 0)
		close(ast->fd);
	free_tree(ast->child);
	free(ast);
}

void	free_tree_list(t_ast *ast)
{
	t_d_list	*tmp;
	t_d_list	*tmp1;

	tmp = ast->args;
	while (tmp)
	{
		free_tree((t_ast *)tmp->content);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
	tmp = ast->redir;
	while (tmp)
	{
		free_tree((t_ast *)tmp->content);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
	free(ast);
}

void	free_tree_pipline(t_ast *ast)
{
	t_d_list	*tmp;
	t_d_list	*tmp1;

	tmp = ast->children;
	while (tmp)
	{
		free_tree((t_ast *)tmp->content);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
	free(ast);
}

void	free_tree_op(t_ast *ast)
{
	free_tree(ast->left);
	free_tree(ast->right);
	free(ast);
}
