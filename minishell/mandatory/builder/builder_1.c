/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/03 13:33:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

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
	}
	else
		builder->cmd = NULL;
	return (builder);
}

/**
 * @brief will append a list to another list
 * 			 unlike ft_d_lstadd_back that add only one node
 * 
 * @param lst 
 * @param newnode list to append
 */
void	ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode)
{
	t_d_list	*last;

	if (!newnode)
		exit(15);
	printf(" wwwww w wwwww\n");
	if (*lst)
	{
		last = ft_d_lstlast(*lst);
		newnode->prev = last;
		last->next = newnode;
	}
	else
		*lst = newnode;
}

/**
 * @brief will build a Linked List of t_builder from a ast tree AST_PIPELINE
 * 
 * @param ast 
 * @return t_d_list* 
 */
t_d_list	*builder_build_pipline(t_ast *ast)
{
	t_d_list	*tmp;
	t_d_list	*build;

	build = NULL;
	tmp = ast->children;
	while (tmp)
	{
		if (((t_ast *)tmp->content)->type == AST_PIPELINE)
			ft_d_lstadd_back_v2(&build, \
			builder_build_op((t_ast *)tmp->content));
		else
			ft_d_lstadd_back(&build, \
			ft_d_lstnew(builder_build_list((t_ast *)tmp->content)));
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
t_d_list	*builder_build_op(t_ast *ast)
{
	t_builder	*build;

	build = (t_builder *)malloc(sizeof(t_builder));
	if (ast->type_token == TOKEN_AND)
		build->type = B_AND;
	if (ast->type_token == TOKEN_OR)
		build->type = B_OR;
	build->left = builder_build(ast->left);
	build->right = builder_build(ast->right);
	return (ft_d_lstnew(build));
}
