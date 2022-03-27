/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 14:08:20 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->token = get_next_token(lexer);
	return (parser);
}

t_token	*parser_eat(t_parser *parser, t_e_token type)
{
	if (parser->token->type != type)
	{
		printf("[Parser]: Unexpected token near %s\n", parser->token->value);
		exit(1);
	}
	parser->token = get_next_token(parser->lexer);
	return (parser->token);
}

t_ast	*parse(t_parser *parser)
{
	(void)parser;
	return (init_ast(AST_LIST));
}

t_ast		*parse_text(t_parser *parser)
{
	t_ast	*ast;
	char	*text;

	text = ft_strdup(parser->token->value);
	parser_eat(parser, TOKEN_TEXT);
	if(parser->token->type == TOKEN_TEXT)
	{
		ast = init_ast(AST_LIST);
		ast->value = text;
		return (ast);
	}
	ast = init_ast(AST_LIST);
	ast->value = parser->token->value;
	parser_eat(parser, TOKEN_TEXT);
	return (ast);
}
