/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sh_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:03:08 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	exec_file_sh(t_cmd *cmd)
{
	char	**tmp;

	tmp = cmd->args;
	cmd->args = clone_args(cmd->args);
	free(tmp);
	if (execve(cmd->args[0], cmd->args, g_global.env) == -1)
	{
		perror("minishell:");
		exit(errno);
	}
}

char	**clone_args(char **args)
{
	int		i;
	char	**new;

	i = 0;
	while (args[++i])
		;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = -1;
	new[0] = ft_strdup("/bin/sh");
	while (args[++i])
	{
		new[i + 1] = ft_strdup(args[i]);
		free(args[i]);
	}
	new[i + 1] = NULL;
	return (new);
}
