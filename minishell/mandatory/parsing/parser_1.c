/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 21:37:29 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"	

t_parser	*parser_init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->token = lexer_next_token(lexer);
	return (parser);
}

t_token		*parser_parser_advance(t_parser *parser, t_e_token type)
{
	if (parser->token->type == type)
		parser->token = lexer_next_token(parser->lexer);
	else
		parser_syntax_error(parser->token->value);
	return (parser->token);
}

t_ast		*parser_parse(t_parser *parser)
{
	if (parser->token->type == TOKEN_LPAREN)
		return (parser_parse_paren(parser));
	return (parser_parse_pipeline(parser));
}

void		parser_syntax_error(char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
	exit(EXIT_SYNTAX_ERROR);
}

int			is_redir(t_token *token)
{
	if (token->type == TOKEN_RIN)
		return (1);
	else if (token->type == TOKEN_DRIN)
		return (1);
	else if (token->type == TOKEN_ROUT)
		return (1);
	else if (token->type == TOKEN_DROUT)
		return (1);
	else
		return (0);
}