/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:27 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/24 13:02:10 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **envp)
{
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PWD", 4))
		i++;
	return (envp[i] + 4);
}

int	main(int ac, char **av, char **env)
{
	char	*path;

	path = get_path(env);
	printf("=> %s\n", path);
	return (0);
}
