/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:05:50 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 06:29:11 by asouinia         ###   ########.fr       */
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

char	*get_cmd_full_path(char **envp, char *cmd)
{
	char	*path;
	char	**all_paths;
	int		i;

	(void)envp;
	if ((cmd[0] == '.' && cmd[1] == '/'))
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	all_paths = parse_paths();
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
