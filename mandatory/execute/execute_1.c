/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:34:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/19 19:55:01 by asouinia         ###   ########.fr       */
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
	DIR		*dir;

	
	dir = opendir(cmd->args[0]);
	if (dir)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			write(2, "minishell: ", 12);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": is a directory\n", 18);
			closedir(dir);
			exit(126);
		}
		closedir(dir);
	}
	str = get_cmd_full_path(envp, cmd->args[0]);
	if (!str)
	{
		str = cmd->args[0];
	}
	dir = opendir(str);
	if (access(str, X_OK) || dir)
	{
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen(str));
		if (dir && ft_strchr(str, '/'))
			write(2, ": is a directory\n", 18);
		else if (access(str, F_OK) && ft_strchr(str, '/'))
			write(2, ": No such file or directory\n", 29);
		else if (access(str, X_OK) && ft_strchr(str, '/'))
			write(2, ": Permission denied\n", 21);
		else
			write(2, ": command not found\n", 21);
		if (dir)
		{
			closedir(dir);
			if (ft_strchr(str, '/'))
				exit(126);
		}
		exit(127);
	}
	if (execve(str, cmd->args, envp) == -1)
	{
		perror("minishell:");
		exit(errno);		
	}
}

char	*lower(char *str)
{
	int		i;
	char	*s;

	i = -1;
	s = ft_strdup(str);
	while (str[++i])
		s[i] = ft_tolower(str[i]);
	return (s);
}

int	execbuilt(t_cmd *cmd)
{
	char	*str;

	str = lower(cmd->args[0]);
	if ((!ft_strncmp(str,"env",ft_strlen("env"))))
		return (showenv(g_global.env), 1);
	else if ((!ft_strncmp(str,"export",ft_strlen("export"))))
		return(export(cmd->args), 1);
	else if ((!ft_strncmp(str,"exit",ft_strlen("exit"))))
	{
		free(str);
		if (cmd->args[1])
			exit(ft_atoi(cmd->args[1]));
		else
			exit(0);
	}
	else if ((!ft_strncmp(str,"cd",ft_strlen("cd"))))
		return (change_dir(&(g_global.env), cmd->args[1]), 1);
	else if ((!ft_strncmp(str,"pwd",ft_strlen("pwd"))))
		return (printf("%s\n", get_path(g_global.env)), 1);
	else if ((!ft_strncmp(str,"unset",ft_strlen("unset"))))
		return (unset_env(&(g_global.env), cmd->args[1]), 1);
	return (free(str), 0);	
}

void	export(char **args)
{
	int		i;
	char	*key;
	char	*egale;
	char	*value;
	
	if (!args[1])
		return (showexport());
	i = 0;
	while (args[++i])
	{
		value = NULL;
		key = ft_strdup(args[i]);
		egale = ft_strchr(key, '=');
		if (egale)
		{

			*egale = '\0';
			value = ++egale;
			addenv(&(g_global.env), key, value);
		}
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", key);
		}
		free(key);
	}
	
	
}

int	exec_cmmand(t_cmd *cmd, char **env, int fd_pipe_in)
{
	int		pid;
	char	*str;

	if (execbuilt(cmd))
		return (-2);
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
		str = lower(cmd->args[0]);
		if (!ft_strncmp(str,"echo",ft_strlen("echo")))
		{
			printf("echo\n");
			free(str);
			exit(0);
		}
		free(str);
		exec_inter(cmd, env);
	}
	return (pid);
}