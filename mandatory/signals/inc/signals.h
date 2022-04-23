/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:26:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 19:01:50 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include "../../inc/global.h"
# include "../../../libft/libft.h"

void	signal_init(int sig);
void	signal_ign(int sig);
void	signal_ign2(int sig);
int		is_minishell(void);

#endif