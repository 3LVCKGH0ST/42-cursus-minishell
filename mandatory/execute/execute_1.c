/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:34:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 18:53:59 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

static void	exec_inter_check_file(char *str, DIR *dir)
{
	int	c;

	if (access(str, X_OK) || dir)
	{
		c = 1;
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen(str));
		if (dir && ft_strchr(str, '/'))
			write(2, ": is a directory\n", 18);
		else if (access(str, F_OK) && ft_strchr(str, '/'))
			write(2, ": No such file or directory\n", 29);
		else if (access(str, X_OK) && ft_strchr(str, '/'))
			write(2, ": Permission denied\n", 21);
		else
		{
			write(2, ": command not found\n", 21);
			c = 0;
		}
		if (dir && ft_strchr(str, '/'))
			exit(126);
		(dir) && closedir(dir);
		if (!c)
			exit(127);
		exit(126);
	}
}

static void	exec_inter_check_script(char **str, char *arg)
{
	*str = arg;
	if ((*str)[0] != '.' || (*str)[1] != '/')
	{
		write(2, "minishell: ", 12);
		write(2, *str, ft_strlen(*str));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

static void	exec_inter(t_cmd *cmd, char **envp)
{
	char	*str;
	DIR		*dir;

	dir = opendir(cmd->args[0]);
	if (dir && ft_strchr(cmd->args[0], '/'))
	{
		write(2, "minishell: ", 12);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": is a directory\n", 18);
		closedir(dir);
		exit(126);
	}
	(dir) && closedir(dir);
	str = get_cmd_full_path(envp, cmd->args[0]);
	if (!str)
		exec_inter_check_script(&str, cmd->args[0]);
	dir = opendir(str);
	exec_inter_check_file(str, dir);
	execve(str, cmd->args, envp);
	if (errno == 8)
		exec_file_sh(cmd);
	perror("minishell:");
	exit(errno);
}

static void	exec_cmd_inter(t_cmd *cmd, char **env, int fd_pipe_in)
{
	char	*str;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (dup2(cmd->inout[0], 0) < 0 || dup2(cmd->inout[1], 1) < 0)
	{
		perror("minishell");
		exit(errno);
	}
	if (fd_pipe_in > 0)
		close(fd_pipe_in);
	str = lower(cmd->args[0]);
	if (!ft_strncmp(str, "echo", ft_strlen("echo")))
	{
		ft_echo(cmd->args);
		free(str);
		exit(0);
	}
	free(str);
	exec_inter(cmd, env);
}

int	exec_cmmand(t_cmd *cmd, char **env, int fd_pipe_in)
{
	int		pid;

	if (g_global.lastcmd)
		free(g_global.lastcmd);
	g_global.lastcmd = ft_strdup(cmd->args[0]);
	if (execbuilt(cmd))
		return (-2);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell:");
		exit(errno);
	}
	if (pid == 0)
		exec_cmd_inter(cmd, env, fd_pipe_in);
	return (pid);
}
