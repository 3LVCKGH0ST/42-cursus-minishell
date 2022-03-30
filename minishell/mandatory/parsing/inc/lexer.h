/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:36:35 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 19:27:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "../../libft/libft.h"
# include "./token.h"

typedef struct s_lexer
{
	char	*src;
	size_t	i;
}				t_lexer;

t_lexer	*lexer_init_lexer(char *src);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_quoted_string(t_lexer *lexer,	char quote);
t_token	*lexer_collect_text(t_lexer *lexer);
t_token	*lexer_collect_id(t_lexer *lexer);
t_token	*lexer_adv_w_tok(t_lexer *lexer, t_token *token);
void	lexer_advance_lexer(t_lexer *lexer);
void	lexer_skip_whitespace_lexer(t_lexer *lexer);
char	*to_str(char c);
#endif
