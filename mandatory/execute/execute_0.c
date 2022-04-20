/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:57:51 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/20 22:02:59 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	execute(t_d_list *node)
{
	t_cmd	*cmd;
	char	*tmp;

	((t_builder *)node->content)->pid = -1;
	if (g_global.fd_error)
	{
		errno = g_global.fd_error;
		tmp = ft_strjoin("minishell: ", g_global.fd_file_error);
		perror(tmp);
		free(tmp);
	}
	else
	{
		cmd = ((t_builder *)node->content)->cmd;
		if (cmd->redir_in)
			cmd->inout[0] = \
			((t_redir *)ft_d_lstlast(cmd->redir_in)->content)->fd;
		else if (node->prev)
			cmd->inout[0] = ((t_builder *)node->prev->content)->pipefd[0];
		else
			cmd->inout[0] = ((t_builder *)node->content)->inout[0];
		if (cmd->redir_out)
			cmd->inout[1] = \
			((t_redir *)ft_d_lstlast(cmd->redir_out)->content)->fd;
		else if (node->next)
			cmd->inout[1] = ((t_builder *)node->content)->pipefd[1];
		if (cmd->args && cmd->args[0])
		{
			((t_builder *)node->content)->pid = exec_cmmand(cmd, g_global.env, \
			((t_builder *)node->content)->pipefd[0]);
			if (((t_builder *)node->content)->pid == -2)
			{
				((t_builder *)node->content)->pid = -1;
				((t_builder *)node->content)->status = g_global.exit_code;
			}
		}
	}
	if (node->next)
		close(((t_builder *)node->content)->pipefd[1]);
	if (node->prev)
		close(((t_builder *)node->prev->content)->pipefd[0]);
	if (node->content)
		close_cmd_fds(node);
}

void	close_cmd_fds(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->fd > 0)
			close(redir_tmp->fd);
		tmp = tmp->next;
	}
	tmp = ((t_builder *)node->content)->cmd->redir_out;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->fd > 0)
			close(redir_tmp->fd);
		tmp = tmp->next;
	}
}
