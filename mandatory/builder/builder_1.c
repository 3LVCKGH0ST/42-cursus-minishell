/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/24 00:02:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

static	void	builder_init_builder_inter(t_builder *builder)
{
	builder->pipefd[1] = 1;
	builder->pipefd[0] = 0;
	builder->inout[1] = 1;
	builder->inout[0] = 0;
	builder->status = 0;
	builder->fd_file_error = NULL;
	builder->fd_error = 0;
}

/**
 * @brief initializes a new builder
 * 
 * @param type 
 * @return t_builder* 
 */
t_builder	*builder_init_builder(t_builder_type type)
{
	t_builder	*builder;

	builder = (t_builder *)malloc(sizeof(t_builder));
	if (!builder)
		return (NULL);
	builder->type = type;
	builder->left = NULL;
	builder->right = NULL;
	if (type == B_CMD)
	{
		builder->cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (!builder->cmd)
			return (NULL);
		builder->cmd->redir_in = NULL;
		builder->cmd->redir_out = NULL;
		builder->cmd->args = NULL;
		builder->cmd->inout[1] = 1;
		builder->cmd->inout[0] = 0;
	}
	else
		builder->cmd = NULL;
	builder_init_builder_inter(builder);
	return (builder);
}

/**
 * @brief will build a Linked List of t_builder from a ast tree AST_PIPELINE
 * 
 * @param ast 
 * @return t_d_list* 
 */
t_d_list	*builder_build_pipline(t_ast *ast, char **env)
{
	t_d_list	*tmp;
	t_d_list	*build;

	build = NULL;
	tmp = ast->children;
	while (tmp)
	{
		if (((t_ast *)tmp->content)->type == AST_PIPELINE)
			ft_d_lstadd_back_v2(&build, \
			builder_build_pipline((t_ast *)tmp->content, env));
		else if (((t_ast *)tmp->content)->type == AST_OP)
			ft_d_lstadd_back(&build, \
			builder_build_op((t_ast *)tmp->content, env));
		else
			ft_d_lstadd_back(&build, \
			ft_d_lstnew(builder_build_list((t_ast *)tmp->content, env)));
		tmp = tmp->next;
	}
	return (build);
}

/**
 * @brief will build a Linked List of t_builder from a ast tree AST_OP
 * 
 * @param ast 
 * @return t_d_list* 
 */
t_d_list	*builder_build_op(t_ast *ast, char **env)
{
	t_builder	*build;

	build = (t_builder *)malloc(sizeof(t_builder));
	if (ast->type_token == TOKEN_AND)
		build->type = B_AND;
	if (ast->type_token == TOKEN_OR)
		build->type = B_OR;
	build->left = builder_build(ast->left, env);
	build->right = builder_build(ast->right, env);
	return (ft_d_lstnew(build));
}

/**
 * @brief 	will build a Linked List of t_builder from a ast tree
 * 
 * @param ast 
 * @return t_d_list* 
 */
t_d_list	*builder_build(t_ast *ast, char **env)
{
	if (ast == NULL)
		return (NULL);
	else if (ast->type == AST_PIPELINE)
		return (builder_build_pipline(ast, env));
	else if (ast->type == AST_OP)
		return (builder_build_op(ast, env));
	return (NULL);
}
