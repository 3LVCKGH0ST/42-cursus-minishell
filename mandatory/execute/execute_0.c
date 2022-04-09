/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:57:51 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/09 05:14:11 by asouinia         ###   ########.fr       */
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
		cmd = node->content;
		if (cmd->redir_in)
			cmd->inout[0] = ((t_redir *)ft_d_lstlast(cmd->redir_in)->content)->fd;
		else if (node->prev)
			cmd->inout[0] = ((t_builder *)node->prev->content)->pipefd[0];
		if (cmd->redir_out)
			cmd->inout[1] = ((t_redir *)ft_d_lstlast(cmd->redir_out)->content)->fd;
		printf("execute  %s\n", ( (t_builder *)node->content)->cmd->args[0]);
	}
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

	tmp = ((t_builder *)node->content)->cmd->redir_in;
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
			here_doc_run(redir_tmp);
		tmp = tmp->next;
	}
}

int	here_doc_run(t_redir *here_doc)
{
	char		*str;
	int			fd[2];

	if (pipe(fd) < 0)
		return (-1);
	str = readline(">");
	while (ft_strncmp(here_doc->file, str, ft_strlen(here_doc->file)))
	{
		ft_putstr_fd(str, fd[1]);
		free(str);
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
