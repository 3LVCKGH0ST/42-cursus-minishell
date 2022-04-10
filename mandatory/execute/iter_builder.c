/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/10 03:28:32 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	iter_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;
	int			i;

	//printf("oen oen oen\n");
	tmp = build;
	while (tmp)
	{
		i = -1;
		if (((t_builder *)tmp->content)->type == B_CMD)
		{
			if (tmp->next)
			{
				if (pipe(((t_builder *)tmp->content)->pipefd) != -1)
					execute(tmp);
			}
			else
				execute(tmp);
		}
		else
			iter_builder_op((t_builder *)tmp->content);
		tmp = tmp->next;
	}
	tmp = build;
	while (tmp)
	{
		if (((t_builder *)tmp->content)->type == B_CMD && ((t_builder *)tmp->content)->pid >= 0)
		{
			waitpid(((t_builder *)tmp->content)->pid, &((t_builder *)tmp->content)->status, 0);	
		}
		tmp = tmp->next;
	}
}

void	iter_builder_op(t_builder *build)
{
	t_d_list	*last;

	build->pid = -1;
	if (pipe(build->pipefd) == -1)
		return ;
 	last = ft_d_lstlast(build->left); 
	((t_builder *)last->content)->pipefd[1] = build->pipefd[1];
	((t_builder *)build->left->content)->inout[0] = build->inout[0];
	build->status = ((t_builder *)last->content)->status;
	iter_builder(build->left);
	build->status = ((t_builder *)last->content)->status;
	if ((build->type == B_AND && build->status == 0) ||
		(build->type == B_OR && build->status != 0))
	{
		last = ft_d_lstlast(build->right);
		((t_builder *)last->content)->pipefd[1] = build->pipefd[1];
		((t_builder *)build->right->content)->inout[0] = build->inout[0];
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
	{
		//printf("dup2  {%d}{%d}\n", b->inout[0], b->inout[1]);
		b->inout[0] = 0;
		b->inout[1] = 1;
		if (build->prev)
		{
			b->inout[0] = ((t_builder *)build->prev->content)->pipefd[0];
		}
		iter_builder_op(b);
	}
}
