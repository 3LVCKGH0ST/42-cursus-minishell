/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:04:13 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 19:05:35 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief wirte a string in the console
 * 
 * @param str string
 * @param newline = 1 ? with new ligne : without
 */

void	ft_echo(char *str)
{
	char	**sp;
	int		i;
	int		j;
	int		n;
	int		cache;

	i = -1;
	n = 0;
	cache = 0;
	if (str)
	{
		sp = ft_split(str, ' ');
		while (sp[++i])
		{
			j = -1;
			while (sp[i][++j])
			{
				if (sp[i][0] == '-')
				{
					if (sp[i][j] == 'n' && j != 0)
					{
						n = 1;
						cache = i + 1;
					}
					else if (j != 0)
					{
						n = 0;
						break ;
					}
				}
			}
			if (n == 0 && cache != 0)
			{
				while (sp[i])
				{
					printf("%s", sp[i++]);
					if (i == sizeof(sp) / sizeof(sp)[0])
						printf(" ");
				}
				printf("%%\n");
				return ;
			}
		}
		if (cache)
		{
			while (sp[cache])
			{
				printf("%s ", sp[cache++]);
				if (cache == sizeof(sp) / sizeof(sp)[0])
						printf(" ");
			}
			printf("\n");
		}
	}
}
