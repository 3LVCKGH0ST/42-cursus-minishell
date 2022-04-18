/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:13 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/18 22:51:51 by mbalagui         ###   ########.fr       */
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
		if (g_global.exp[i + 1] && \
		ft_strncmp(g_global.exp[i], g_global.exp[i + 1], \
		ft_strlen(g_global.exp[i + 1])) > 0)
		{
			tmp = ft_strdup(g_global.exp[i]);
			free(g_global.exp[i]);
			g_global.exp[i] = malloc(ft_strlen(g_global.exp[i + 1]));
			g_global.exp[i] = ft_strdup(g_global.exp[i + 1]);
			free(g_global.exp[i + 1]);
			g_global.exp[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = -1;
		}
	}
}

void	showexport(void)
{
	int		i;

	i = -1;
	shortexport();
	while (g_global.exp[++i])
		printf("declare -x %s\n", g_global.exp[i]);
}
