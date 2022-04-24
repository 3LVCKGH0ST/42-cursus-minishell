/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:57:51 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 18:53:59 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

static void	execute_inter(t_d_list *node)
{
	t_cmd	*cmd;

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
	if (cmd->args && cmd->args[0] && cmd->args[0][0])
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

void	execute(t_d_list *node)
{
	((t_builder *)node->content)->pid = -1;
	if (((t_builder *)node->content)->fd_error)
		print_error_fd(node);
	else
		execute_inter(node);
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

int	execbuilt(t_cmd *cmd)
{
	char	*str;

	str = lower(cmd->args[0]);
	if ((!ft_strncmp(str, "env", ft_strlen("env"))))
		return (free(str), showenv(g_global.env, cmd->inout[1]), 1);
	else if ((!ft_strncmp(str, "export", ft_strlen("export"))))
		return (free(str), ft_export(cmd->args, cmd->inout[1]), 1);
	else if ((!ft_strncmp(str, "exit", ft_strlen("exit"))))
		return (free(str), ft_exit(cmd->args), 1);
	else if ((!ft_strncmp(str, "cd", ft_strlen("cd"))))
		return (free(str), change_dir(&(g_global.env), cmd->args[1]), 1);
	else if ((!ft_strncmp(str, "pwd", ft_strlen("pwd"))))
	{
		ft_putstr_fd(get_path(g_global.env), cmd->inout[1]);
		return (free(str), ft_putchar_fd('\n', cmd->inout[1]), 1);
	}
	else if ((!ft_strncmp(str, "unset", ft_strlen("unset"))))
		return (free(str), unset_env(&(g_global.env), cmd->args[1]), 1);
	return (free(str), 0);
}

void	ft_export(char **args, int fd)
{
	int		i;
	char	*key;
	char	*egale;
	char	*value;

	if (!args[1])
		return (showexport(fd));
	i = 0;
	while (args[++i])
	{
		value = NULL;
		key = ft_strdup(args[i]);
		egale = ft_strchr(key, '=');
		if (!egale)
			setexport(key, NULL);
		else
		{
			*egale = '\0';
			value = ++egale;
			setexport(key, value);
		}
		free(key);
	}
}
