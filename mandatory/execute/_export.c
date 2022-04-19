/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:13 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/19 21:45:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

static	int	get_len(void)
{
	int	i;

	i = -1;
	while (g_global.env[++i])
		;
	return (i);
}

void	shortexport(void)
{
	int		i;
	int		s;
	char	*tmp;

	s = get_len();
	i = -1;
	while (++i < s)
	{
		if (g_global.exp[i + 1] && g_global.exp[i] && \
		ft_strncmp(g_global.exp[i], g_global.exp[i + 1], \
		ft_strlen(g_global.exp[i + 1])) > 0)
		{
			tmp = ft_strdup(g_global.exp[i]);
			free(g_global.exp[i]);
			//g_global.exp[i] = malloc(ft_strlen(g_global.exp[i + 1]));
			g_global.exp[i] = ft_strdup(g_global.exp[i + 1]);
			free(g_global.exp[i + 1]);
			g_global.exp[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = -1;
		}
	}
}

void	showexport(int fd)
{
	int		i;
	int		j;

	i = -1;
	shortexport();
	while (g_global.exp[++i])
	{
		if (!ft_strchr(g_global.exp[i], '='))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(g_global.exp[i], fd);
			ft_putchar_fd('\n', fd);	
		}
		else
		{
			j = -1;
			ft_putstr_fd("declare -x ", fd);
			while ( g_global.exp[i][++j] != '=')
				ft_putchar_fd(g_global.exp[i][j], fd);
			ft_putstr_fd("=\"", fd);
			while ( g_global.exp[i][++j])
				ft_putchar_fd(g_global.exp[i][j], fd);
			ft_putstr_fd("\"\n", fd);
		}
	}
}
