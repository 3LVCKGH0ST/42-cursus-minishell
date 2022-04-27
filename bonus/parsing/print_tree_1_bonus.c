/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:30:04 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/27 03:19:01 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/print_tree_bonus.h"

void	print_tree_id(t_ast *ast)
{
	t_d_list	*tmp;

	ft_putstr_fd(" ", 1);
	tmp = ast->children;
	while (tmp)
	{
		ft_putstr_fd((tmp->content), 1);
		tmp = tmp->next;
	}
	ft_putchar_fd(' ', 1);
}

void	print_tree_redir(t_ast *ast)
{
	if (ast->type_token == TOKEN_RIN)
		ft_putstr_fd("<", 1);
	if (ast->type_token == TOKEN_DRIN)
		ft_putstr_fd("<<", 1);
	if (ast->type_token == TOKEN_ROUT)
		ft_putstr_fd(">", 1);
	if (ast->type_token == TOKEN_DROUT)
		ft_putstr_fd(">>", 1);
	print_tree(ast->child);
}

void	print_tree_list(t_ast *ast)
{
	t_d_list	*tmp;

	tmp = ast->args;
	while (tmp)
	{
		print_tree((t_ast *)tmp->content);
		tmp = tmp->next;
	}
	tmp = ast->redir;
	while (tmp)
	{
		print_tree((t_ast *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_tree_pipline(t_ast *ast)
{
	t_d_list	*tmp;

	tmp = ast->children;
	while (tmp)
	{
		print_tree((t_ast *)tmp->content);
		tmp = tmp->next;
		if (tmp)
			ft_putstr_fd(" | ", 1);
	}
}

void	print_tree_op(t_ast *ast)
{
	print_tree(ast->left);
	if (ast->type_token == TOKEN_AND)
		ft_putstr_fd(" && ", 1);
	if (ast->type_token == TOKEN_OR)
		ft_putstr_fd(" || ", 1);
	print_tree(ast->right);
}
