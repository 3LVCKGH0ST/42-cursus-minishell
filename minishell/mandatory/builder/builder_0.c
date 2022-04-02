/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/02 00:33:23 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

t_d_list *get_tree_builder(t_ast *ast)
{
	if (ast == NULL)
		return (NULL);
	else if (ast->type == AST_PIPELINE)
		return (get_tree_builder_pipline(ast));	
	else if (ast->type == AST_OP)
		return (get_tree_builder_op(ast));
	return (NULL);
}

t_builder *get_tree_builder_list(t_ast *ast)
{
	t_d_list	*tmp;
	t_builder	*build;
	int			i;

	i = 0;
	tmp = ast->args;
	build = (t_builder *)malloc(sizeof(t_builder));
	build->type = B_CMD;
	build->cmd = malloc(sizeof(t_cmd));
	build->cmd->redir_in = NULL;
	build->cmd->redir_out = NULL;
	build->cmd->args = malloc(sizeof(char *) * (ft_d_list_size(tmp) + 1));
	build->cmd->args[ft_d_list_size(tmp)] = NULL;
	while (tmp)
	{
		build->cmd->args[i++] = get_tree_builder_id((t_ast *)tmp->content);
		tmp = tmp->next;
	}
	tmp = ast->redir;
	while (tmp)
	{
		if(((t_ast *)tmp->content)->type_token == TOKEN_RIN)
			ft_d_lstadd_back(&(build->cmd->redir_in), ft_d_lstnew(get_tree_builder_redir((t_ast *)tmp->content)));
		else if(((t_ast *)tmp->content)->type_token == TOKEN_DRIN)
			ft_d_lstadd_back(&(build->cmd->redir_in), ft_d_lstnew(get_tree_builder_redir((t_ast *)tmp->content)));
		else
			ft_d_lstadd_back(&(build->cmd->redir_out), ft_d_lstnew(get_tree_builder_redir((t_ast *)tmp->content)));
		tmp = tmp->next;
	}
	return (build);
}

char	*get_tree_builder_id(t_ast *ast)
{
	return (ast->value);
}

t_redir	*get_tree_builder_redir(t_ast *ast)
{
	t_redir	*redir;

	redir->type = ast->type_token;
	redir->file = get_tree_builder_id(ast->child);
}

t_d_list *get_tree_builder_pipline(t_ast *ast)
{
	t_d_list	*tmp;
	t_d_list	*build;

	build = NULL;
	tmp = ast->children;
	while (tmp)
	{
		ft_d_lstadd_back(&build, ft_d_lstnew(get_tree_builder((t_ast *)tmp->content)));
		tmp = tmp->next;
	}
}

t_d_list *get_tree_builder_op(t_ast *ast)
{
	t_d_list	*tmp;

	get_tree_builder(ast->left);
	if (ast->type_token == TOKEN_AND)
		ft_putstr_fd(" && ", 1);
	if (ast->type_token == TOKEN_OR)
		ft_putstr_fd(" || ", 1);
	get_tree_builder(ast->right);
	
}