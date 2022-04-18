/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:45:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/18 06:10:18 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	change_dir(char ***env, char *to)
{
	char	*pwd;
	char	*path;

	if (!to)
	{
		to = get_env_var(g_global.env, "HOME");
		if (!to)
		{
			write(2, "minishell: cd: HOME not set\n", 30);
			g_global.exit_code = 1;
			return ;
		}
		to = ft_strchr(to, '=') + 1;		
	}
	if (access(to, F_OK) || !opendir(to))
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
	}
}