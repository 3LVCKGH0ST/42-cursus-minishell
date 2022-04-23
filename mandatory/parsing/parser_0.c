/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:43:57 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 05:21:10 by asouinia         ###   ########.fr       */
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
	parser->token = lexer_next_token(lexer);
	if (!parser->token)
		return (NULL);
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
	return (parser_syntax_error(parser->token->value), NULL);
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
	ast = parser_parse_v2(parser, left);
	if (!ast)
		return (free_tree(ast), NULL);
	return (ast);
}

t_ast	*parser_parse_v2(t_parser *parser, t_ast *prev)
{
	t_ast		*right;
	t_ast		*ast;
	t_ast		*tmp;
	t_e_token	type;

	type = parser->token->type;
	parser_parser_advance(parser, type);
	right = parser_parse_term(parser);
	if (right == NULL)
		return (free_tree(prev), NULL);
	ast = ast_init_ast(AST_OP);
	ast->type_token = type;
	ast->left = prev;
	ast->right = right;
	if (!is_op(parser->token))
		return (ast);
	tmp = parser_parse_v2(parser, ast);
	if (!tmp)
		return (free_tree(tmp), NULL);
	return (tmp);
}

t_ast	*parser_parse_term(t_parser *parser)
{
	return (parser_parse_pipeline(parser));
}
