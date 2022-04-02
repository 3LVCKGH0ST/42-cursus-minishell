/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:30:04 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/01 19:47:31 by asouinia         ###   ########.fr       */
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

void	print_tree_id(t_ast *ast)
{
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ast->value, 1);
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
	//printf("left: %d\n", ast->type_token);
	if (ast->type_token == TOKEN_AND)
		ft_putstr_fd(" && ", 1);
	if (ast->type_token == TOKEN_OR)
		ft_putstr_fd(" || ", 1);
	print_tree(ast->right);
}
