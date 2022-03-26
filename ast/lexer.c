/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:21:23 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/26 22:56:39 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->src = src;
	lexer->i = 0;
	return (lexer);
}

void	advance_lexer(t_lexer *lexer)
{
	if (lexer->src[lexer->i] && lexer->i < ft_strlen(lexer->src))
		lexer->i++;
}

void	skip_whitespace_lexer(t_lexer *lexer)
{
	while (lexer->src[lexer->i] && \
			(lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t'))
		lexer->i++;
}

char	*to_str(char c)
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
	char	*tmp;

	advance_lexer(lexer);
	value = ft_strdup("");
	while (lexer->src[lexer->i] && lexer->src[lexer->i] != quote)
	{
		tmp = value;
		value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
		free(tmp);
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

	value = to_str(lexer->src[lexer->i]);
	while (lexer->src[lexer->i] && ft_isalnum(lexer->src[lexer->i]))
	{
		value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
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
		else if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
			return (collect_quoted_string(lexer, lexer->src[lexer->i]));
		else if (ft_isalnum(lexer->src[lexer->i]))
			return (collect_text(lexer));
		else if (lexer->src[lexer->i] == '|' && lexer->src[lexer->i + 1] == '|')
			return (adv_w_tok(lexer, init_token(ft_strdup("||"), TOKEN_OR)));
		else if (lexer->src[lexer->i] == '&' && lexer->src[lexer->i + 1] == '&')
			return (adv_w_tok(lexer, init_token(ft_strdup("&&"), TOKEN_AND)));
		else if (lexer->src[lexer->i] == '>' && lexer->src[lexer->i + 1] == '>')
			return (adv_w_tok(lexer, init_token(ft_strdup(">>"), TOKEN_DROUT)));
		else if (lexer->src[lexer->i] == '<' && lexer->src[lexer->i + 1] == '<')
			return (adv_w_tok(lexer, init_token(ft_strdup("<<"), TOKEN_DRIN)));
		else if (lexer->src[lexer->i] == '(')
			return (adv_w_ton(lexer, init_token(ft_strdup("("), TOKEN_LPAREN)));
		else if (lexer->src[lexer->i] == ')')
			return (adv_w_tok(lexer, init_token(ft_strdup(")"), TOKEN_RPAREN)));
		else if (lexer->src[lexer->i] == '|')
			return (adv_w_tok(lexer, init_token(ft_strdup("|"), TOKEN_PIPE)));
		else if (lexer->src[lexer->i] == '>')
			return (adv_w_tok(lexer, init_token(ft_strdup(">"), TOKEN_ROUT)));
		else if (lexer->src[lexer->i] == '<')
			return (adv_w_tok(lexer, init_token(ft_strdup("<"), TOKEN_RIN)));
	}
	return (init_token(to_str('\0'), TOKEN_EOF));
}

t_token	*adv_w_tok(t_lexer *lexer, t_token *token)
{
	size_t	i;

	i = 1;
	while (i < ft_strlen(token->value))
	{
		advance_lexer(lexer);
		i++;
	}
	return (token);
}
