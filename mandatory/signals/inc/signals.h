/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:29:09 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/20 22:12:54 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include "../../inc/global.h"

void	signal_init(int sig);
void	signal_ign(int sig);
void	signal_ign2(int sig);
#endif