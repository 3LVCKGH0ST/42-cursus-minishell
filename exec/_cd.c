/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:45:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 17:57:08 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_dir(char ***env, char *to)
{
	char	*pwd;
	char	*path;

	(void)to;
	pwd = get_path(*env);
	addenv(&(*env), "OLDPWD", pwd);
	chdir(to);
	path = getcwd(NULL, 0);
	addenv(&(*env), "PWD", path);
	free(path);
}
