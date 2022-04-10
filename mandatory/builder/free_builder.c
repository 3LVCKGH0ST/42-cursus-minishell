/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/10 08:05:12 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

void	builder_free_builder_redir(t_d_list *redir)
{
	t_d_list	*tmp;
	t_d_list	*tmp1;
	t_redir		*redir_tmp;

	tmp = redir;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->file)
			free(redir_tmp->file);
		free(redir_tmp);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}

void	builder_free_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;
	t_d_list	*tmp1;
	int			i;

	tmp = build;
	while (tmp)
	{
		i = -1;
		if (((t_builder *)tmp->content)->type == B_CMD)
		{
			while (((t_builder *)tmp->content)->cmd->args[++i])
				free(((t_builder *)tmp->content)->cmd->args[i]);
			free(((t_builder *)tmp->content)->cmd->args);
			builder_free_builder_redir(\
			((t_builder *)tmp->content)->cmd->redir_in);
			builder_free_builder_redir(\
			((t_builder *)tmp->content)->cmd->redir_out);
			free(((t_builder *)tmp->content)->cmd);
			free(((t_builder *)tmp->content));
		}
		else
			builder_free_builder_op((t_builder *)tmp->content);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}

void	builder_free_builder_op(t_builder *build)
{
	builder_free_builder(build->left);
	builder_free_builder(build->right);
	free(build);
}

void	builder_free_builder(t_d_list *build)
{
	t_builder	*b;

	if (!build)
		return ;
	b = (t_builder *)build->content;
	if (b->type == B_CMD)
		builder_free_builder_pipline(build);
	else if (b->type == B_OR || b->type == B_AND)
	{
		builder_free_builder_op((t_builder *)build->content);
		free(build);
	}
}
