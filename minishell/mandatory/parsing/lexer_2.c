/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:27:47 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 09:57:30 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lexer.h"

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace_lexer(lexer);
		else if (!is_reserved_token(lexer->c))
			return (lexer_collect_id(lexer));
		else if (lexer->c == '|' && lexer->cc == '|')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("||"), TOKEN_OR)));
		else if (lexer->c == '&' && lexer->cc == '&')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("&&"), TOKEN_AND)));
		else if (lexer->c == '>' && lexer->cc == '>')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup(">>"), TOKEN_DROUT)));
		else if (lexer->c == '<' && lexer->cc == '<')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("<<"), TOKEN_DRIN)));
		else if (lexer->c == '(')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("("), TOKEN_LPAREN)));
		else if (lexer->c == ')')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup(")"), TOKEN_RPAREN)));
		else if (lexer->c == '|')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("|"), TOKEN_PIPE)));
		else if (lexer->c == '>')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup(">"), TOKEN_ROUT)));
		else if (lexer->c == '<')
			return (lexer_advance_w_token(lexer, init_token(ft_strdup("<"), TOKEN_RIN)));
		else
		{
			fprintf(stderr, "Error: Unexpected token : %c\n", lexer->c);
			exit(1);
		}
	}
	return (init_token(ft_strdup("'\\n'"), TOKEN_EOF));
}

static char	*get_str_quoted(char *prev, t_lexer *lexer)
{
	char	quote;
	char	*tmp;

	quote = lexer->c;
	tmp = prev;
	prev = ft_strjoin(prev, to_str(lexer->c));
	free(tmp);
	lexer_advance(lexer);
	while (lexer->c && lexer->c != quote)
	{
		tmp = prev;
		prev = ft_strjoin(prev, to_str(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	tmp = prev;
	prev = ft_strjoin(prev, to_str(lexer->c));
	free(tmp);
	if (lexer->c != quote)
	{
		fprintf(stderr, "Error: Unmatched quote\n");
		exit(1);
	}
	return (prev);
}

/**
 * @brief get tocken id (aka words with thiere quted value) 
 * 
 * @param lexer 
 * @return ** t_token*  token type => TOKEN_ID and 
 * 			token value ex: ss"hello   "sss kks  ==> ss"hello"sss
 */
t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*tmp;

	value = to_str(lexer->c);
	lexer_advance(lexer);
	while (lexer->c && !is_reserved_token(lexer->c))
	{
		tmp = value;
		value = ft_strjoin(value, to_str(lexer->c));
		free(tmp);
		if (lexer->c == '\'' || lexer->c == '"')
		{
			value = get_str_quoted(value, lexer);
			tmp = value;
			value = ft_strjoin(value, to_str(lexer->c));
			free(tmp);
		}
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_ID));
}
