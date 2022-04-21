/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:37:36 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute_bonus.h"

int	getspec(char	**arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		j = -1;
		if (arg[i][0] != '-' || arg[i][1] != 'n')
			return (i);
		while (arg[i][++j])
		{
			if (arg[i][0] == '-' && j == 0)
				j++;
			if (arg[i][j] != 'n')
				return (i);
		}
		g_global.withnewline = 0;
		i++;
	}
	if (arg[i - 1][0] == '-' && arg[i - 1][1] == 'n')
		return (0);
	return (-1);
}

void	ft_echo(char	**arg)
{
	int	i;

	g_global.withnewline = 1;
	i = getspec(arg);
	if (i == -1)
	{
		printf("\n");
		return ;
	}
	if (i == 0)
		return ;
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
	}
	if (g_global.withnewline)
		printf("\n");
}
