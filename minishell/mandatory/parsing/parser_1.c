/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/02 23:01:53 by asouinia         ###   ########.fr       */
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

t_token	*parser_parser_advance(t_parser *parser, t_e_token type)
{
	if (parser->token->type == type)
		parser->token = lexer_next_token(parser->lexer);
	else
		parser_syntax_error(parser->token->value);
	return (parser->token);
}

t_ast	*parser_parse(t_parser *parser)
{
	t_ast	*left;
	t_ast	*ast;

	left = parser_parse_term(parser);
	if (!is_op(parser->token))
		return (left);
	ast = ast_init_ast(AST_OP);
	ast->type_token = parser->token->type;
	if (parser->token->type == TOKEN_AND)
		parser_parser_advance(parser, TOKEN_AND);
	else if (parser->token->type == TOKEN_OR)
		parser_parser_advance(parser, TOKEN_OR);
	ast->left = left;
	ast->right = parser_parse(parser);
	return (ast);
}

t_ast	*parser_parse_term(t_parser *parser)
{
	if (parser->token->type == TOKEN_LPAREN)
		return (parser_parse_paren(parser));
	return (parser_parse_pipeline(parser));
}
