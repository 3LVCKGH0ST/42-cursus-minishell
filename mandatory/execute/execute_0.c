/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:57:51 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/10 00:51:49 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	execute(t_d_list *node)
{
	t_cmd	*cmd;

	open_here_doc(node);
	if (open_in_files(node))
	{
		open_out_files(node);
		cmd = ((t_builder *)node->content)->cmd;
		//printf("{%s}{%p}{%p}\n",((t_builder *)node->content)->cmd->args[0], node->next,cmd->redir_out);
		if (cmd->redir_in)
			cmd->inout[0] = ((t_redir *)ft_d_lstlast(cmd->redir_in)->content)->fd;
		else if (node->prev)
		{
			cmd->inout[0] = ((t_builder *)node->prev->content)->pipefd[0];
			//printf("({%d})", ((t_builder *)node->prev->content)->pipefd[0]);
		}
		else
			cmd->inout[0] = ((t_builder *)node->content)->inout[0];
		if (cmd->redir_out)
		{
			//printf("{%s}\n", ((t_builder *)node->content)->cmd->args[0]);			
			cmd->inout[1] = ((t_redir *)ft_d_lstlast(cmd->redir_out)->content)->fd;
		}
		else if (node->next)
		{
			cmd->inout[1] = ((t_builder *)node->content)->pipefd[1];
		}
		//printf("pipes  {%d}{%d} {%s}\n", ((t_builder *)node->content)->pipefd[0], ((t_builder *)node->content)->pipefd[1] , cmd->args[0]);
		if (cmd->args && cmd->args[0])
		{
			((t_builder *)node->content)->pid = exec_cmmand(cmd, g_global.env);
			//close(cmd->inout[0]);
			//close(cmd->inout[1]);
			//waitpid(((t_builder *)node->content)->pid, &((t_builder *)node->content)->status, 0);
			if (node->next)
				close(((t_builder *)node->content)->pipefd[1]);
			 if (node->prev)
				close(((t_builder *)node->prev->content)->pipefd[0]);
		}
	}
	if (node->content)
		close_cmd_fds(node);
}

int	open_in_files(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;
	char		*tmp_str;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_RIN)
		{
			redir_tmp->fd = open(redir_tmp->file, O_RDONLY);
			if (redir_tmp->fd < 0)
			{
				tmp_str = ft_strjoin("minishell: ", redir_tmp->file);
				perror(tmp_str);
				return (free(tmp_str), 0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	open_out_files(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;
	char		*tmp_str;

	tmp = ((t_builder *)node->content)->cmd->redir_out;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_ROUT)
			redir_tmp->fd = open(redir_tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			redir_tmp->fd = open(redir_tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir_tmp->fd < 0)
		{
			tmp_str = ft_strjoin("minishell: ", redir_tmp->file);
			perror(tmp_str);
			return (free(tmp_str), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	open_here_doc(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_DRIN)
			redir_tmp->fd = here_doc_run(redir_tmp);
		tmp = tmp->next;
	}
}

int	here_doc_run(t_redir *here_doc)
{
	char		*str;
	char		*tmp;
	int			fd[2];

	if (pipe(fd) < 0)
		return (-1);
	str = readline(">");
	while (ft_strncmp(here_doc->file, str, ft_strlen(here_doc->file)))
	{
		tmp = ft_strjoin(str, "\n");
		ft_putstr_fd(tmp, fd[1]);
		free(str);
		free(tmp);
		str = readline(">");
	}
	free(str);
	close(fd[1]);
	return (fd[0]);
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
