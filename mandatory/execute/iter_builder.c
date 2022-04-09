/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/09 02:18:50 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	iter_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;
	int			i;

	tmp = build;
	while (tmp)
	{
		i = -1;
		if (((t_builder *)tmp->content)->type == B_CMD)
		{
			execute(tmp);
		}
		else
			iter_builder_op((t_builder *)tmp->content);
		tmp = tmp->next;
	}
}

void	iter_builder_op(t_builder *build)
{
	t_d_list	*last;

	if (pipe(build->pipefd) == -1)
		return ;
 	last = ft_d_lstlast(build->left);
	((t_builder *)last->content)->pipefd[1] = build->pipefd[1];
	((t_builder *)last->content)->pipefd[0] = build->pipefd[0];
	build->status = ((t_builder *)last->content)->status;
	iter_builder(build->left);
	build->status = ((t_builder *)last->content)->status;
	if ((build->type == B_AND && build->status == 0) ||
		(build->type == B_OR && build->status != 0))
	{
		last = ft_d_lstlast(build->right);
		if (build->type == B_OR)
		{
			((t_builder *)last->content)->pipefd[1] = build->pipefd[1];
			((t_builder *)last->content)->pipefd[0] = build->pipefd[0];
		}
		else
		{
			((t_builder *)last->content)->pipefd[1] = 1;
			((t_builder *)last->content)->pipefd[0] = -1;
		}
		iter_builder(build->right);
		build->status = ((t_builder *)last->content)->status;
	}
}

void	iter_builder(t_d_list *build)
{
	t_builder	*b;

	if (!build)
		return ;
	b = (t_builder *)build->content;
	if (b->type == B_CMD)
		iter_builder_pipline(build);
	else if (b->type == B_OR || b->type == B_AND)
		iter_builder_op((t_builder *)build->content);
}
