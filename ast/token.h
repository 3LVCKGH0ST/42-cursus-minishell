/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:25:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/25 23:12:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../libft/libft.h"

typedef enum e_token {
	TOKEN_LBRACE,	//? (
	TOKEN_RBRACE,	//? )
	TOKEN_OR,		//? ||
	TOKEN_AND,		//? &&
	TOKEN_PIPE,		//? |
	TOKEN_RIN,		//? <
	TOKEN_ROUT,		//? >
	TOKEN_DRIN,		//? <<
	TOKEN_DROUT,	//? >>
	TOKEN_SQUOTE,	//? '
	TOKEN_DQUOTE,	//? "
	TOKEN_EOF,		//? 0
}	t_e_token;

typedef struct s_token
{
	char		*value;
	t_e_token	type;
}	t_token;

t_token	*init_token(char *value, t_e_token type);

#endif
