/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:34:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/10 07:59:29 by asouinia         ###   ########.fr       */
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
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (cmd);
}

static void	exec_inter(t_cmd *cmd, char **envp)
{
	char	*str;

	str = get_cmd_full_path(envp, cmd->args[0]);
	if (access(str, X_OK) < 0)
	{
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen(str));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		exit(COMMAND_NOT_FOUND_ERROR);
	}
	if (execve(str, cmd->args, envp) == -1)
	{
		perror("minishell:");
		exit(errno);		
	}
}

int	exec_cmmand(t_cmd *cmd, char **env)
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
		if (dup2(cmd->inout[0], 0) < 0 || dup2(cmd->inout[1], 1) < 0)
		{
			perror("minishell");
			exit(errno);
		}
		//printf("inout  {%d}{%d} {%s}\n", cmd->inout[0], cmd->inout[1] , cmd->args[0]);
		//close(cmd->inout[0]);
		//close(cmd->inout[1]);
		exec_inter(cmd, env);
	}
	return (pid);
}