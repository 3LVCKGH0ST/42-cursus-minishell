/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:34:05 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/29 17:43:36 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->src[lexer->i] && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->src[lexer->i] == ' ' || lexer->src[lexer->i] == '\t')
			skip_whitespace_lexer(lexer);
		else if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
			return (collect_quoted_string(lexer, lexer->src[lexer->i]));
		else if (ft_isalnum(lexer->src[lexer->i]))
			return (collect_id(lexer));
		else if (lexer->src[lexer->i] == '|' && lexer->src[lexer->i + 1] == '|')
			return (adv_w_tok(lexer, init_token(ft_strdup("||"), TOKEN_OR)));
		else if (lexer->src[lexer->i] == '&' && lexer->src[lexer->i + 1] == '&')
			return (adv_w_tok(lexer, init_token(ft_strdup("&&"), TOKEN_AND)));
		else if (lexer->src[lexer->i] == '>' && lexer->src[lexer->i + 1] == '>')
			return (adv_w_tok(lexer, init_token(ft_strdup(">>"), TOKEN_DROUT)));
		else if (lexer->src[lexer->i] == '<' && lexer->src[lexer->i + 1] == '<')
			return (adv_w_tok(lexer, init_token(ft_strdup("<<"), TOKEN_DRIN)));
		else if (lexer->src[lexer->i] == '(')
			return (adv_w_tok(lexer, init_token(ft_strdup("("), TOKEN_LPAREN)));
		else if (lexer->src[lexer->i] == ')')
			return (adv_w_tok(lexer, init_token(ft_strdup(")"), TOKEN_RPAREN)));
		else if (lexer->src[lexer->i] == '|')
			return (adv_w_tok(lexer, init_token(ft_strdup("|"), TOKEN_PIPE)));
		else if (lexer->src[lexer->i] == '>')
			return (adv_w_tok(lexer, init_token(ft_strdup(">"), TOKEN_ROUT)));
		else if (lexer->src[lexer->i] == '<')
			return (adv_w_tok(lexer, init_token(ft_strdup("<"), TOKEN_RIN)));
		else
		{
			fprintf(stderr, "Error: Unexpected token : %c\n", lexer->src[lexer->i]);
			exit(1);
		}
	}
	return (init_token(to_str('\0'), TOKEN_EOF));
}

t_token	*collect_text(t_lexer *lexer)
{
	char	*value;
	char	*tmp;

	value = to_str(lexer->src[lexer->i]);
	advance_lexer(lexer);
	while (lexer->src[lexer->i] && ft_isalnum(lexer->src[lexer->i]))
	{
		tmp = value;
		value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
		free(tmp);
		lexer->i++;
	}
	return (init_token(value, TOKEN_TEXT));
}


//t_token	*collect_id(t_lexer *lexer)
//{
//	char	*value;
//	char	*tmp;
//	char	quote;

//	value = to_str(lexer->src[lexer->i]);
//	advance_lexer(lexer);
//	while (lexer->src[lexer->i] && \
//		(ft_isalnum(lexer->src[lexer->i]) || lexer->src[lexer->i] == '\'' \
//		|| lexer->src[lexer->i] == '"'))
//	{
//		tmp = value;
//		printf("value 2: %s\n", value);
//		value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
//		free(tmp);
//		if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
//		{
//			quote = lexer->src[lexer->i];
//			//advance_lexer(lexer);
//			lexer->i++;
//			while (lexer->src[lexer->i] && lexer->src[lexer->i] != quote)
//			{
//				tmp = value;
//				printf("value 1: %s      {%c}\n", value, lexer->src[lexer->i]);
//				value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
//				free(tmp);
//				lexer->i++;
//			}
//			//tmp = value;
//			////printf("value 1: %s      {%c}\n", value, lexer->src[lexer->i]);
//			//value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
//			//free(tmp);
//			////lexer->i++;
//			//if (lexer->src[lexer->i] == quote)
//			//	advance_lexer(lexer);
//		}
//		lexer->i++;
//	}
	
//	return (init_token(value, TOKEN_ID));
//}


t_token	*collect_id(t_lexer *lexer)
{
	char	*value;
	char	*tmp;
	char	quote;

	value = to_str(lexer->src[lexer->i]);
	advance_lexer(lexer);
	while (lexer->src[lexer->i] && \
		(ft_isalnum(lexer->src[lexer->i]) || lexer->src[lexer->i] == '\'' \
		|| lexer->src[lexer->i] == '"'))
	{
		tmp = value;
		value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
		free(tmp);
		if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
		{
			quote = lexer->src[lexer->i];
			lexer->i++;
			while (lexer->src[lexer->i] && lexer->src[lexer->i] != quote)
			{
				tmp = value;
				value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
				free(tmp);
				lexer->i++;
			}
			if (lexer->src[lexer->i] == '\'' || lexer->src[lexer->i] == '"')
			{
				tmp = value;
				value = ft_strjoin(value, to_str(lexer->src[lexer->i]));
				free(tmp);
			}
			else
			{
				fprintf(stderr, "Error: Unmatched quote\n");
				exit(1);
			}
		}
		advance_lexer(lexer);
	}
	return (init_token(value, TOKEN_ID));	
}


t_token	*adv_w_tok(t_lexer *lexer, t_token *token)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(token->value))
	{
		advance_lexer(lexer);
		i++;
	}
	return (token);
}
