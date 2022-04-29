/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_builder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/27 03:41:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute_bonus.h"

static void	iter_builder_pipline_inter(t_d_list *tmp)
{
	t_builder	*b;

	while (tmp)
	{
		b = tmp->content;
		b->inout[0] = 0;
		b->inout[1] = 1;
		if (tmp->next)
		{
			if (pipe(b->pipefd) < 0)
				return (perror("minishell:"), exit(errno));
			b->inout[1] = b->pipefd[1];
		}
		if (tmp->prev)
			b->inout[0] = ((t_builder *)tmp->prev->content)->pipefd[0];
		if (b->type == B_CMD)
			execute(tmp);
		else
			iter_builder_op(tmp);
		if (tmp->next)
			close(b->pipefd[1]);
		if (tmp->prev)
			close(((t_builder *)tmp->prev->content)->pipefd[0]);
		tmp = tmp->next;
	}	
}

void	iter_builder(t_d_list *build)
{
	t_d_list	*tmp;
	t_builder	*b;

	if (!build)
		return ;
	iter_builder_pipline_inter(build);
	tmp = build;
	while (tmp)
	{
		b = (t_builder *)tmp->content;
		if (b->pid > 0)
			waitpid(b->pid, &(b->status), 0);
		tmp = tmp->next;
	}
}

void	iter_builder_op(t_d_list *builder)
{
	t_builder	*build;
	int			id;

	build = (t_builder *)builder->content;
	id = fork();
	if (id < 0)
		return (perror("minishell:"), exit(errno));
	build->pid = id;
	if (id != 0)
		return ;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (dup2(build->inout[0], 0) < 0 || dup2(build->inout[1], 1) < 0)
		return (perror("minishell:"), exit(errno));
	if (build->pipefd[0] > 0)
		close(build->pipefd[0]);
	iter_builder(build->left);
	build->status = ((t_builder *)ft_d_lstlast(build->left)->content)->status;
	if ((build->type == B_AND && build->status != 0) || \
		(build->type == B_OR && build->status == 0))
		exit(build->status);
	iter_builder(build->right);
	build->status = ((t_builder *)ft_d_lstlast(build->right)->content)->status;
	exit(build->status);
}

void	iter_builder_no(t_d_list *builder)
{
	t_builder	*build;

	build = (t_builder *)builder->content;
	iter_builder(build->left);
	build->status = ((t_builder *)ft_d_lstlast(build->left)->content)->status;
	if ((build->type == B_AND && build->status != 0) || \
		(build->type == B_OR && build->status == 0))
		return ;
	iter_builder(build->right);
	build->status = ((t_builder *)ft_d_lstlast(build->right)->content)->status;
}
