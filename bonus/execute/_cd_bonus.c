/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:45:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/23 06:54:30 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute_bonus.h"

static int	change_dir_inter(char **to)
{
	if (!*to)
	{
		*to = get_env_var(g_global.env, "HOME");
		if (!*to)
		{
			write(2, "minishell: cd: HOME not set\n", 30);
			g_global.exit_code = 1;
			return (1);
		}
		*to = ft_strchr(*to, '=') + 1;
	}
	else if (ft_strncmp(*to, "~", 1) == 0)
		*to = "/Users/asouinia";
	return (0);
}

void	change_dir(char ***env, char *to)
{
	char	*pwd;
	char	*path;
	DIR		*dir;

	if (change_dir_inter(&to))
		return ;
	dir = opendir(to);
	if (access(to, F_OK) || !dir)
	{
		perror("minishell: cd");
		g_global.exit_code = 1;
	}
	else
	{
		pwd = get_path(*env);
		addenv(&(*env), "OLDPWD", pwd);
		chdir(to);
		path = getcwd(NULL, 0);
		addenv(&(*env), "PWD", path);
		free(path);
		g_global.exit_code = 0;
		closedir(dir);
	}
}
