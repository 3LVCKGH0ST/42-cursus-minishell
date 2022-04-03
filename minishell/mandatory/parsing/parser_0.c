/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/03 17:45:43 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"	

t_ast	*parser_parse_pipeline(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*tmp;

	if (!parser)
		return (NULL);
	ast = ast_init_ast(AST_PIPELINE);
	if (parser->token->type == TOKEN_LPAREN)
	{
		tmp = parser_parse_paren(parser);
		if (!tmp)
			return (NULL);
		ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
	}
	else
	{
		tmp = parser_parse_list(parser);
		if (!tmp)
			return (NULL);
		ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
	}
	while (parser->token->type == TOKEN_PIPE)
	{
		if (!parser_parser_advance(parser, TOKEN_PIPE))
			return (NULL);
		if (parser->token->type == TOKEN_LPAREN)
		{
			tmp = parser_parse_paren(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
		}
		else
		{
			tmp = parser_parse_list(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
		}
	}
	return (ast);
}

t_ast	*parser_parse_list(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*tmp;
	t_token	*token;

	if (!parser)
		return (NULL);
	ast = ast_init_ast(AST_LIST);
	token = parser->token;
	if (token->type != TOKEN_ID && !is_redir(token))
		return (NULL);
	while (token->type == TOKEN_ID || \
	is_redir(token) || token->type == TOKEN_LPAREN)
	{
		if (token->type == TOKEN_ID)
		{
			tmp = parser_parse_id(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->args), ft_d_lstnew(tmp));
		}
		else if (is_redir(token))
		{
			tmp = parser_parse_redir(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->redir), ft_d_lstnew(tmp));
		}
		else
		{
			if (token->type == TOKEN_LPAREN)
				parser_parser_advance(parser, TOKEN_LPAREN);
			return (NULL);
		}
		token = parser->token;
	}
	return (ast);
}

t_ast	*parser_parse_redir(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	if (!parser)
		return (NULL);
	token = parser->token;
	parser_parser_advance(parser, token->type);
	ast = ast_init_ast(AST_REDIR);
	ast->type_token = token->type;
	ast->child = parser_parse_id(parser);
	if (!ast->child)
		return (NULL);
	return (ast);
}

t_ast	*parser_parse_id(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	if (!parser)
		return (NULL);
	token = parser->token;
	if (!parser_parser_advance(parser, TOKEN_ID))
		return (NULL);
	ast = ast_init_ast(AST_ID);
	ast->value = token->value;
	return (ast);
}

t_ast	*parser_parse_paren(t_parser *parser)
{
	t_ast	*ast;

	if (!parser)
		return (NULL);
	if (!parser_parser_advance(parser, TOKEN_LPAREN))
		return (NULL);
	ast = parser_parse(parser);
	if (!parser_parser_advance(parser, TOKEN_RPAREN))
		return (NULL);
	if (parser->token->type == TOKEN_ID)
	{
		parser_syntax_error(parser->token->value);
		return (NULL);
	}
	return (ast);
}
