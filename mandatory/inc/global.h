/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:48:19 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/16 23:30:06 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# define EXIT_SYNTAX_ERROR 258

typedef struct s_global
{
	int		exit_code;
	int		prev_exit_code;
	int  	fd_error;
	char	*fd_file_error;
	char	**env;
	char	**envp;
	int		current_pid;
}t_global;
t_global	g_global;
#endif