/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:34:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/17 02:07:56 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

char	*get_env_var(char **envp, char *env_var)
{
	int	i;

	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], env_var, ft_strlen(env_var)) == 0)
		{
			if (envp[i][ft_strlen(env_var)] == '=')
			{
				return (envp[i]);
			}
		}
	}
	return (NULL);
}

void	free_2d(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

char	**get_paths(char **envp)
{
	char	**paths;
	char	**result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_split(get_env_var(envp, "PATH"), ':');
	if (!result)
		return (NULL);
	while (result[i++])
		;
	paths = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = ft_substr(result[0], 4, ft_strlen(result[0]));
	paths[0] = ft_strjoin(tmp, "/");
	free(tmp);
	while (result[++i])
		paths[i] = ft_strjoin(result[i], "/");
	free_2d(result);
	paths[i] = NULL;
	return (paths);
}

char	*get_cmd_full_path(char **envp, char *cmd)
{
	char	*path;
	char	**all_paths;
	int		i;

	all_paths = get_paths(envp);
	i = -1;
	while (all_paths && all_paths[++i])
	{
		path = ft_strjoin(all_paths[i], cmd);
		if (!access(path, F_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

static void	exec_inter(t_cmd *cmd, char **envp)
{
	char	*str;

	str = get_cmd_full_path(envp, cmd->args[0]);
	if (!str)
	{
		str = cmd->args[0];
		if ( cmd->args[0][0] != '/' && (cmd->args[0][0] != '.' || cmd->args[0][1] != '/'))
		{
			write(2, "minishell: ", 12);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": command not found\n", 21);
			exit(127);
		}
	}
	if (access(str, X_OK) || opendir(str))
	{
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen(str));
		if (access(str, F_OK))
			write(2, ": No such file or directory\n", 29);
		else if (access(str, X_OK))
			write(2, ": Permission denied\n", 21);
		else
			write(2, ": command not found\n", 21);
		exit(127);
	}
	if (execve(str, cmd->args, envp) == -1)
	{
		perror("minishell:");
		exit(errno);		
	}
}

int	exec_cmmand(t_cmd *cmd, char **env, int fd_pipe_in)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell:");
		exit(errno);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (dup2(cmd->inout[0], 0) < 0 || dup2(cmd->inout[1], 1) < 0)
		{
			perror("minishell");
			exit(errno);
		}
		if (fd_pipe_in > 0)
			close(fd_pipe_in);
		exec_inter(cmd, env);
	}
	return (pid);
}