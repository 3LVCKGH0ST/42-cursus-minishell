/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:21:23 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 09:26:25 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lexer.h"

t_lexer	*lexer_init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer || !src)
		return (NULL);
	lexer->src = src;
	lexer->i = 0;
	lexer->c = src[0];
	lexer->tokens = NULL;
	return (lexer);
}

t_token	*lexer_advance_w_token(t_lexer *lexer, t_token *token)
{
	int		i;

	i = 0;
	while (i < ft_strlen(token->value))
	{
		lexer_advance(lexer);
		i++;
	}
	return (token);
}

/**
 * @brief make lexer point to the next charater
 * 
 * @param lexer 
 */
void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

/**
 * @brief skip whitespace characters (' ', '\t')
 * 
 * @param lexer 
 */
void	lexer_skip_whitespace_lexer(t_lexer *lexer)
{
	while (lexer->c && (lexer->c == ' ' || lexer->c == '\t'))
		lexer_advance(lexer);
}
