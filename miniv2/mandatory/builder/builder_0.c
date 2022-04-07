/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/07 02:05:17 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

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

/**
 * @brief will add the redirection to the right Linked List
 * 
 * @param tmp 
 * @param build 
 */
static void	builder_list_builder_inter(t_d_list *tmp, t_builder *build, \
char **env)
{
	if (((t_ast *)tmp->content)->type_token == TOKEN_RIN)
		ft_d_lstadd_back(&(build->cmd->redir_in), \
		ft_d_lstnew(builder_build_redir((t_ast *)tmp->content, env)));
	else if (((t_ast *)tmp->content)->type_token == TOKEN_DRIN)
		ft_d_lstadd_back(&(build->cmd->redir_in), \
		ft_d_lstnew(builder_build_redir((t_ast *)tmp->content, env)));
	else
		ft_d_lstadd_back(&(build->cmd->redir_out), \
		ft_d_lstnew(builder_build_redir((t_ast *)tmp->content, env)));
}

/**
 * @brief will add the args to cmd and set redirections
 * 
 * @param ast 
 * @return t_builder* 
 */
t_builder	*builder_build_list(t_ast *ast, char **env)
{
	t_d_list	*tmp;
	t_builder	*build;
	int			i;

	i = 0;
	tmp = ast->args;
	build = builder_init_builder(B_CMD);
	build->cmd->args = malloc(sizeof(char *) * (ft_d_lstsize(tmp) + 1));
	build->cmd->args[ft_d_lstsize(tmp)] = NULL;
	while (tmp)
	{
		build->cmd->args[i++] = builder_build_id((t_ast *)tmp->content, env);
		tmp = tmp->next;
	}
	tmp = ast->redir;
	while (tmp)
	{
		builder_list_builder_inter(tmp, build, env);
		tmp = tmp->next;
	}
	return (build);
}

/**
 * @brief will ger value of AST_ID and expand it
 * 
 * @param ast
 * @return char* 
 */
char	*builder_build_id(t_ast *ast, char **env)
{
	return (builder_expand_id(ast->value, env));
}

/**
 * @brief will return a redirection struct with value and type set from
 * 			AST_REDIR tree
 * 
 * @param ast 
 * @return t_redir* 
 */
t_redir	*builder_build_redir(t_ast *ast, char **env)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = ast->type_token;
	redir->file = builder_build_id(ast->child, env);
	return (redir);
}
