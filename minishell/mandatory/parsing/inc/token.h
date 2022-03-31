/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:25:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 09:07:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../../libft/libft.h"

typedef enum e_token {
	TOKEN_ID,
	TOKEN_TEXT,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_RIN,
	TOKEN_ROUT,
	TOKEN_DRIN,
	TOKEN_DROUT,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_EOF
}	t_e_token;

typedef struct s_token
{
	char		*value;
	t_e_token	type;
}	t_token;

t_token	*init_token(char *value, t_e_token type);
void	free_token(t_token *token);
#endif
