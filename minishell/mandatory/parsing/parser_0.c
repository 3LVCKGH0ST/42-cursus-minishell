/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/03 17:59:17 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"	

t_ast	*parser_parse_pipeline(t_parser *parser)
{
	t_ast	*ast;

	ast = ast_init_ast(AST_PIPELINE);
	if (parser->token->type == TOKEN_LPAREN)
		ft_d_lstadd_back(&(ast->children), \
		ft_d_lstnew(parser_parse_paren(parser)));
	else
		ft_d_lstadd_back(&(ast->children), \
		ft_d_lstnew(parser_parse_list(parser)));
	while (parser->token->type == TOKEN_PIPE)
	{
		parser_parser_advance(parser, TOKEN_PIPE);
		if (parser->token->type == TOKEN_LPAREN)
			ft_d_lstadd_back(&(ast->children), \
			ft_d_lstnew(parser_parse_paren(parser)));
		else
			ft_d_lstadd_back(&(ast->children), \
			ft_d_lstnew(parser_parse_list(parser)));
	}
	return (ast);
}

t_ast	*parser_parse_list(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	ast = ast_init_ast(AST_LIST);
	token = parser->token;
	if (token->type != TOKEN_ID && !is_redir(token))
		parser_syntax_error(token->value);
	while (token->type == TOKEN_ID || \
	is_redir(token) || token->type == TOKEN_LPAREN)
	{
		if (token->type == TOKEN_ID)
			ft_d_lstadd_back(&(ast->args), \
			ft_d_lstnew(parser_parse_id(parser)));
		else if (is_redir(token))
			ft_d_lstadd_back(&(ast->redir), \
			ft_d_lstnew(parser_parse_redir(parser)));
		else
		{
			if (token->type == TOKEN_LPAREN)
				parser_parser_advance(parser, TOKEN_LPAREN);
			parser_syntax_error(parser->token->value);
		}
		token = parser->token;
	}
	return (ast);
}

t_ast	*parser_parse_redir(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	token = parser->token;
	parser_parser_advance(parser, token->type);
	ast = ast_init_ast(AST_REDIR);
	ast->type_token = token->type;
	ast->child = parser_parse_id(parser);
	return (ast);
}

t_ast	*parser_parse_id(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	token = parser->token;
	parser_parser_advance(parser, TOKEN_ID);
	ast = ast_init_ast(AST_ID);
	ast->value = token->value;
	return (ast);
}

t_ast	*parser_parse_paren(t_parser *parser)
{
	t_ast	*ast;

	parser_parser_advance(parser, TOKEN_LPAREN);
	ast = parser_parse(parser);
	parser_parser_advance(parser, TOKEN_RPAREN);
	if (parser->token->type == TOKEN_ID)
		parser_syntax_error(parser->token->value);
	return (ast);
}
