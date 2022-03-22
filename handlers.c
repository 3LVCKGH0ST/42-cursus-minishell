/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:01:53 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/22 19:11:36 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readinputs(char **read)
{
	char	*str;
	char	**cmds;
	int		i;

	str = *read;
	while (1)
	{
		str = readline("minishell$ : ");
		printf("=> %s\n", str);
		printf("pipe checker %d\n", check_end_start_pipes(str));
		printf("quote checker %d\n", quotescheckers(str, ft_strlen(str)));
		printf("multipipes : %d\n", count_max_multiple_pipes(str));
		cmds = NULL;
		if (count_max_multiple_pipes(str) <= 1 && check_end_start_pipes(str))
			cmds = split_cmds(str);
		free(str);
		i = -1;
		while (cmds && cmds[++i])
		{
			printf("=>\t%s\n", cmds[i]);
		}
	}
}
