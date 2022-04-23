/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:09:55 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:21:35 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lexer.h"

/**
 * @brief 
 * 
 * @param lexer 
 * @return t_token* 
 */
static t_token	*lexer_next_token_extra(t_lexer *lexer)
{
	if (lexer->c == '|')
		return (lexer_set_token(lexer, "|", TOKEN_PIPE));
	else if (lexer->c == '>')
		return (lexer_set_token(lexer, ">", TOKEN_ROUT));
	else if (lexer->c == '<')
		return (lexer_set_token(lexer, "<", TOKEN_RIN));
	else if (!is_reserved_token(lexer))
		return (lexer_collect_id(lexer));
	else
		lexer_syntax_error(to_str(lexer->c));
	return (NULL);
}

/**
 * @brief get the next token and advance the
 * 		 lexer if an unexpected char is found will exit
 * 
 * @param lexer 
 * @return t_token* return the next token
 */
t_token	*lexer_next_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace_lexer(lexer);
		else if (lexer->c == '>' && lexer->cc == '>')
			return (lexer_set_token(lexer, ">>", TOKEN_DROUT));
		else if (lexer->c == '<' && lexer->cc == '<')
			return (lexer_set_token(lexer, "<<", TOKEN_DRIN));
		else
			return (lexer_next_token_extra(lexer));
	}
	return (lexer_set_token(lexer, "'\\n'", TOKEN_EOF));
}
