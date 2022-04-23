/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:27:22 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 18:50:32 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# define EXIT_SYNTAX_ERROR 258
# include "../../double_linked_list/double_linked_list.h"

typedef struct s_global
{
	int			exit_code;
	int			prev_exit_code;
	int			fd_error;
	char		*fd_file_error;
	char		*lastcmd;
	char		**env;
	char		**exp;
	char		**envp;
	int			interupted;
	int			quited;
	int			withnewline;
	t_d_list	*here_docs;
}t_global;
t_global	g_global;

typedef struct s_heredoc
{
	char	*str;
	int		fd[2];
}t_heredoc;

#endif