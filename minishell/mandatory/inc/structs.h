/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:54:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/01 23:07:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
//# include "../../libft/libft.h"
# include "../../double_linked_list/double_linked_list.h"
typedef enum e_redir_types
{
	R_IN,
	R_HEREDOC,
	R_OUT,
	R_OUTAPPEND
}						t_redir_types;

typedef struct s_redir		
{
	t_redir_types	type;
	int				fd;
	char			*file;
}	t_redir;

typedef struct		s_cmd
{
	char			**args;
	int				inout[2];
	int				*pipefd;
	t_d_list		*redir_in;
	t_d_list		*redir_out;
}					t_cmd;


#endif