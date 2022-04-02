/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:21:23 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 18:33:58 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus.h"

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
	if (lexer->src[lexer->i] != quote)
	{
		fprintf(stderr, "Error: Unmatched quote\n");
		exit(1);
	}
	//advance_lexer(lexer);
	advance_lexer(lexer);
	if (quote == '\'')
		return (init_token(value, TOKEN_SQUOTE));
	return (init_token(value, TOKEN_DQUOTE));
}
