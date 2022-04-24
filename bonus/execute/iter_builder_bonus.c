/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_builder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/24 08:48:39 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute_bonus.h"

static void	iter_builder_pipline_inter(t_d_list *tmp)
{
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(((t_builder *)tmp->content)->pipefd) < 0)
			{
				perror("minishell:");
				exit(errno);
			}
		}
		if (((t_builder *)tmp->content)->type == B_CMD)
			execute(tmp);
		else
		{
			if (tmp->next)
				((t_builder *)tmp->content)->inout[1] = \
				((t_builder *)tmp->content)->pipefd[1];
			if (tmp->prev)
				((t_builder *)tmp->content)->inout[0] = \
				((t_builder *)tmp->prev->content)->pipefd[0];
			iter_builder_op(tmp);
			if (tmp->next)
			{
				close(((t_builder *)tmp->content)->pipefd[1]);
			}
		}
		tmp = tmp->next;
	}	
}

void	iter_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;

	tmp = build;
	iter_builder_pipline_inter(tmp);
	tmp = build;
	while (tmp)
	{
		if (((t_builder *)tmp->content)->pid >= 0)
		{
			//if (((t_builder *)tmp->content)->type == B_CMD && tmp->next)
			//{
			//	//printf("{%p}{%d}\n", tmp->next, getpid());
			//	close(((t_builder *)tmp->content)->pipefd[0]);
			//}
			waitpid(((t_builder *)tmp->content)->pid, \
			&((t_builder *)tmp->content)->status, 0);
		}
		tmp = tmp->next;
	}
}

void	iter_builder_op(t_d_list *builder)
{
	t_d_list	*last;
	t_builder	*build;
	int			id;

	build = (t_builder *)builder->content;

	id = fork();
	if (id < 0)
	{
		perror("minishell:");
		exit(errno);
	}
	else if (id == 0)
	{
		printf("%d\n", getpid());
		signal(SIGINT, SIG_DFL);
		build->pid = -1;
		last = ft_d_lstlast(build->left);
		((t_builder *)last->content)->inout[1] = build->inout[1];
		((t_builder *)last->content)->pipefd[1] = build->pipefd[1];
		((t_builder *)build->left->content)->inout[0] = build->inout[0];
		((t_builder *)build->left->content)->pipefd[0] = build->pipefd[0];
		//if (build->pipefd[0])
		//{
		//	dup2(build->pipefd[0], 0);
		//	close(build->pipefd[0]);
		//	build->pipefd[0] = 0;
		//	printf("1{%d}{%d}\n", build->pipefd[0], getpid());
		//}
		iter_builder(build->left);
		build->status = ((t_builder *)last->content)->status;
		if ((build->type == B_AND && build->status == 0) || \
			(build->type == B_OR && build->status != 0))
		{
			last = ft_d_lstlast(build->right);
			((t_builder *)last->content)->pipefd[1] = build->inout[1];
			((t_builder *)build->right->content)->inout[0] = build->inout[0];
			iter_builder(build->right);
			build->status = ((t_builder *)last->content)->status;
		}
		exit(build->status);
	}
	else
	{
		if (build->pipefd[0])
		{
			close(build->pipefd[0]);
		}
		build->pid = id;
	}
}

void	iter_builder(t_d_list *build)
{
	//t_builder	*b;

	if (!build)
		return ;
	//b = (t_builder *)build->content;
	//if (b->type == B_CMD)
		iter_builder_pipline(build);
	//else if (b->type == B_OR || b->type == B_AND)
	//{
		//b->inout[0] = 0;
		//b->inout[1] = 1;
		//iter_builder_op(b);
	//}
}
