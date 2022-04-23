/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:28:44 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 19:00:43 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/signals.h"

void	signal_init(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global.prev_exit_code = 1;
	g_global.exit_code = 1;
}

void	signal_ign(int sig)
{
	(void)sig;
	g_global.interupted = 1;
}

void	signal_ign2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(2);
}

int	is_minishell(void)
{
	int	i;

	i = 0;
	if (g_global.lastcmd[0] != '.' || g_global.lastcmd[1] != '/')
		return (!ft_strncmp(g_global.lastcmd, "minishell", 10));
	while (g_global.lastcmd[++i] == '/')
		;
	return (!ft_strncmp(g_global.lastcmd + i, "minishell", 10));
}
