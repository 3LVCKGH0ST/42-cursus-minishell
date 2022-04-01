/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:27:47 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/01 16:14:52 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lexer.h"

/**
 * @brief create and add the token to lexer tokens to free them later
 * 			and will advance the lexer
 * 
 * @param lexer 
 * @param value "<<" ">>" or whatever token value
 * @param type token type
 * @return t_token* will return the created token
 */
static t_token	*lexer_set_token(t_lexer *lexer, char *value, t_e_token type)
{
	char	*str;
	t_token	*token;

	str = ft_strdup(value);
	token = init_token(str, type);
	ft_d_lstadd_back(&(lexer->tokens), ft_d_lstnew(token));
	return (lexer_advance_w_token(lexer, token));
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
		else if (lexer->c == '|' && lexer->cc == '|')
			return (lexer_set_token(lexer, "||", TOKEN_OR));
		else if (lexer->c == '&' && lexer->cc == '&')
			return (lexer_set_token(lexer, "&&", TOKEN_AND));
		else if (lexer->c == '>' && lexer->cc == '>')
			return (lexer_set_token(lexer, ">>", TOKEN_DROUT));
		else if (lexer->c == '<' && lexer->cc == '<')
			return (lexer_set_token(lexer, "<<", TOKEN_DRIN));
		else if (lexer->c == '(')
			return (lexer_set_token(lexer, "(", TOKEN_LPAREN));
		else if (lexer->c == ')')
			return (lexer_set_token(lexer, ")", TOKEN_RPAREN));
		else if (lexer->c == '|')
			return (lexer_set_token(lexer, "|", TOKEN_PIPE));
		else if (lexer->c == '>')
			return (lexer_set_token(lexer, ">", TOKEN_ROUT));
		else if (lexer->c == '<')
			return (lexer_set_token(lexer, "<", TOKEN_RIN));
		else if (!is_reserved_token(lexer->c))
			return (lexer_collect_id(lexer));
		else
			lexer_syntax_error(to_str(lexer->c));
	}
	return (init_token(ft_strdup("'\\n'"), TOKEN_EOF));
}
/**
 * @brief Get the str quoted object
 * 
 * @param prev 
 * @param lexer 
 * @return char* 
 */
static char	*get_str_quoted(char *prev, t_lexer *lexer)
{
	char	quote;
	char	*tmp1;
	char	*tmp2;

	quote = lexer->c;
	lexer_advance(lexer);
	while (lexer->c && lexer->c != quote)
	{
		tmp1 = prev;
		tmp2 = to_str(lexer->c);
		prev = ft_strjoin(prev, tmp2);
		free(tmp1);
		free(tmp2);
		lexer_advance(lexer);
	}
	if (lexer->c != quote)
		lexer_quote_error(to_str(quote));
	tmp1 = prev;
	tmp2 = to_str(lexer->c);
	prev = ft_strjoin(prev, tmp2);
	free(tmp1);
	free(tmp2);
	return (prev);
}

/**
 * @brief get tocken id (aka words with thiere quted value) 
 * 
 * @param lexer 
 * @return ** t_token*  token type => TOKEN_ID and 
 * 			token value ex: ss"hello   "sss kks  ==> ss"hello   "sss
 */
t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*tmp1;
	char	*tmp2;
	t_token	*token;

	value = to_str('\0');
	while (lexer->c && !is_reserved_token(lexer->c))
	{
		tmp1 = value;
		tmp2 = to_str(lexer->c);
		value = ft_strjoin(value, tmp2);
		free(tmp1);
		free(tmp2);
		if (lexer->c == '\'' || lexer->c == '"')
			value = get_str_quoted(value, lexer);
		lexer_advance(lexer);
	}
	token = init_token(value, TOKEN_ID);
	ft_d_lstadd_back(&(lexer->tokens), ft_d_lstnew(token));
	return (token);
}
