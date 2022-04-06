/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:43:57 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/06 19:49:16 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/parser.h"

t_parser	*parser_init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser || !lexer)
		return (NULL);
	parser->lexer = lexer;
	return (parser);
}

t_token	*parser_parser_advance(t_parser *parser, t_e_token type)
{
	if (parser->token->type == type)
	{
		parser->token = lexer_next_token(parser->lexer);
		if (parser->token == NULL)
			return (NULL);		
		return (parser->token);
	}
	parser_syntax_error(parser->token->value);
	return (NULL);
}

t_ast	*parser_parse(t_parser *parser)
{
	t_ast	*left;
	t_ast	*ast;

	left = parser_parse_term(parser);
	if (left == NULL)
		return (NULL);
	if (!is_op(parser->token))
		return (left);
	ast = ast_init_ast(AST_OP);
	ast->type_token = parser->token->type;
	if (parser->token->type == TOKEN_AND)
	{
		if (!parser_parser_advance(parser, TOKEN_AND));
			return (NULL);
	}	
	else if (parser->token->type == TOKEN_OR)
	{
		if (!parser_parser_advance(parser, TOKEN_OR));
			return (NULL);
	}
	ast->left = left;
	ast->right = parser_parse(parser);
	if (ast->right == NULL)
		return (NULL);
	return (ast);
}
