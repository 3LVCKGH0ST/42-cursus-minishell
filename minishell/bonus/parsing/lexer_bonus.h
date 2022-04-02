/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:36:35 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 17:56:21 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "../../libft/libft.h"
# include "./token_bonus.h"

typedef struct s_lexer
{
	char	*src;
	size_t	i;
}				t_lexer;

t_lexer	*init_lexer(char *src);
t_token	*get_next_token(t_lexer *lexer);
t_token	*collect_quoted_string(t_lexer *lexer,	char quote);
t_token	*collect_text(t_lexer *lexer);
t_token	*collect_id(t_lexer *lexer);
t_token	*adv_w_tok(t_lexer *lexer, t_token *token);
void	advance_lexer(t_lexer *lexer);
void	skip_whitespace_lexer(t_lexer *lexer);
char	*to_str(char c);
#endif
