/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:21:23 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/26 16:03:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	init_lexer(char *src)
{
	t_lexer	lexer;

	lexer.src = src;
	lexer.i = 0;
	return (lexer);
}

void	advance_lexer(t_lexer *lexer)
{
	while (lexer->src[lexer->i] && lexer->i < ft_strlen(lexer->src))
		lexer->i++;
}

void	skip_whitespace_lexer(t_lexer *lexer)
{
	while (lexer->src[lexer->i] && \
			(lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t'))
		lexer->i++;
}

char	*to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*collect_quoted_string(t_lexer *lexer,	char quote)
{
	char	*value;

	advance_lexer(lexer);
	value = to_string(lexer->src[lexer->i]);
	while (lexer->src[lexer->i] && lexer->src[lexer->i] != quote)
	{
		value = ft_strlcat(value, to_string(lexer->src[lexer->i]), \
							ft_strlen(value) + 1);
		lexer->i++;
	}
	advance_lexer(lexer);
	if (quote == '\'')
		return (init_token(value, TOKEN_SQUOTE));
	return (init_token(value, TOKEN_DQUOTE));
}

t_token	*collect_text(t_lexer *lexer)
{
	char	*value;

	value = to_string(lexer->src[lexer->i]);
	while (lexer->src[lexer->i] && ft_isalnum(lexer->src[lexer->i]))
	{
		value = ft_strlcat(value, to_string(lexer->src[lexer->i]), \
						ft_strlen(value) + 1);
		lexer->i++;
	}
	return (init_token(value, TOKEN_TEXT));
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->src[lexer->i] && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t')
			skip_whitespace_lexer(lexer);
		else if (ft_isalnum(lexer->src[lexer->i]))
			return (collect_text(lexer));
		else if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
			return (collect_quoted_string(lexer, lexer->src[lexer->i]));
		else if (lexer->src[lexer->i] == '|' && lexer->src[lexer->i + 1] == '|')
			return (init_token(ft_strdup("||"), TOKEN_OR));
		else if (lexer->src[lexer->i] == '&' && lexer->src[lexer->i + 1] == '&')
			return (init_token(ft_strdup("&&"), TOKEN_AND));
		else if (lexer->src[lexer->i] == '>' && lexer->src[lexer->i + 1] == '>')
			return (init_token(ft_strdup(">>")), TOKEN_DROUT);
		else if (lexer->src[lexer->i] == '<' && lexer->src[lexer->i + 1] == '<')
			return (init_token(ft_strdup("<<")), TOKEN_DRIN);
		else if (lexer->src[lexer->i] == '(')
			return (init_token(to_string(lexer->src[lexer->i]), TOKEN_LPAREN));
		else if (lexer->src[lexer->i] == ')')
			return (init_token(to_string(lexer->src[lexer->i]), TOKEN_RPAREN));
		else if (lexer->src[lexer->i] == '|')
			return (init_token(to_string(lexer->src[lexer->i]), TOKEN_PIPE));
		else if (lexer->src[lexer->i] == '>')
			return (init_token(to_string(lexer->src[lexer->i]), TOKEN_ROUT));
		else if (lexer->src[lexer->i] == '<')
			return (init_token(to_string(lexer->src[lexer->i]), TOKEN_RIN));
	}
	return (init_token(to_string('\0'), TOKEN_EOF));
}
