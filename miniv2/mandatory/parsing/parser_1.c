/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:43:29 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/08 02:08:16 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"	

t_ast	*parser_parse_pipeline(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*tmp;

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

t_ast	*parser_parse_redir(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	token = parser->token;
	if (!parser_parser_advance(parser, token->type))
		return (NULL);
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

	token = parser->token;
	if (!parser_parser_advance(parser, TOKEN_ID))
		return (NULL);
	ast = ast_init_ast(AST_ID);
	ast->value = ft_strdup(token->value);
	return (ast);
}

t_ast	*parser_parse_list(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*tmp;
	t_token	*token;

	ast = ast_init_ast(AST_LIST);
	token = parser->token;
	if (token->type != TOKEN_ID && !is_redir(token))
		return (parser_syntax_error(token->value), NULL);
	while (token->type == TOKEN_ID || \
	is_redir(token))
	{
		if (token->type == TOKEN_ID)
		{
			tmp = parser_parse_id(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->args), ft_d_lstnew(tmp));
		}
		else
		{
			tmp = parser_parse_redir(parser);
			if (!tmp)
				return (NULL);
			ft_d_lstadd_back(&(ast->redir), ft_d_lstnew(tmp));
		}
		token = parser->token;
	}
	if (token->type == TOKEN_LPAREN)
	{
		parser_parser_advance(parser, TOKEN_LPAREN);
		return (parser_syntax_error(parser->token->value), NULL);
	}
	return (ast);
}
