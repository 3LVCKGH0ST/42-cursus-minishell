/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:54:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:25:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H
//# include "../../libft/libft.h"
# include "../../double_linked_list/double_linked_list.h"
# include "../parsing/inc/token_bonus.h"

typedef struct s_redir
{
	t_e_token		type;
	int				fd;
	char			*file;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	int				inout[2];
	t_d_list		*redir_in;
	t_d_list		*redir_out;
}					t_cmd;

#endif