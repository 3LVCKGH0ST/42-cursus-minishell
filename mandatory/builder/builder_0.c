/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/29 02:01:41 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

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

static void	fill_all_args(t_d_list **tmp, t_d_list *args, t_ast *ast, \
t_builder *build)
{
	t_d_list	*i;
	t_d_list	*j;

	build->fd_error = ast->fd_error;
	build->fd_file_error = ast->fd_file_error;
	i = args;
	while (i)
	{
		j = ((t_ast *)i->content)->children;
		while (j)
		{
			ft_d_lstadd_back(tmp, ft_d_lstnew(ft_strdup(j->content)));
			j = j->next;
		}
		i = i->next;
	}
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
	t_d_list	*tmp2;
	t_builder	*build;
	int			i;

	i = 0;
	tmp = NULL;
	build = builder_init_builder(B_CMD);
	fill_all_args(&tmp, ast->args, ast, build);
	build->cmd->args = malloc(sizeof(char *) * (ft_d_lstsize(tmp) + 1));
	build->cmd->args[ft_d_lstsize(tmp)] = NULL;
	tmp2 = tmp;
	while (tmp)
	{
		build->cmd->args[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	ft_d_lstclear(&tmp2, &free);
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
	(void)env;
	return (ft_strdup(ast->children->content));
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
	redir->fd = ast->fd;
	redir->file = builder_build_id(ast->child, env);
	return (redir);
}
