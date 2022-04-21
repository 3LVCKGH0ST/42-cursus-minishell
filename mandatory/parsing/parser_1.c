/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:43:29 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 00:01:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"

static t_ast	*parser_parse_pipeline_inter(t_parser *parser, t_ast *ast)
{
	t_ast	*tmp;

	while (parser->token->type == TOKEN_PIPE)
	{
		if (!parser_parser_advance(parser, TOKEN_PIPE))
			return (NULL);
		if (parser->token->type == TOKEN_LPAREN)
		{
			tmp = parser_parse_paren(parser);
			if (!tmp)
				return (free_tree(ast), NULL);
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
		}
		else
		{
			tmp = parser_parse_list(parser);
			if (!tmp)
				return (free_tree(ast), NULL);
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
		}
	}
	return (ast);
}

t_ast	*parser_parse_pipeline(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*tmp;

	ast = ast_init_ast(AST_PIPELINE);
	if (parser->token->type == TOKEN_LPAREN)
	{
		tmp = parser_parse_paren(parser);
		if (!tmp)
			return (free_tree(ast), NULL);
		ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
	}
	else
	{
		tmp = parser_parse_list(parser);
		if (!tmp)
			return (free_tree(ast), NULL);
		ft_d_lstadd_back(&(ast->children), ft_d_lstnew(tmp));
	}
	return (parser_parse_pipeline_inter(parser, ast));
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

static int	parser_parse_list_inter(t_token *token, t_ast *ast, \
t_parser *parser)
{
	t_ast	*tmp;

	if (token->type == TOKEN_ID)
	{
		tmp = parser_parse_id(parser);
		if (!tmp)
			return (free_tree(ast), 0);
		ft_d_lstadd_back(&(ast->args), ft_d_lstnew(tmp));
	}
	else
	{
		tmp = parser_parse_redir(parser);
		if (!tmp)
			return (free_tree(ast), 0);
		ft_d_lstadd_back(&(ast->redir), ft_d_lstnew(tmp));
	}
	return (1);
}

t_ast	*parser_parse_list(t_parser *parser)
{
	t_ast	*ast;
	t_token	*token;

	ast = ast_init_ast(AST_LIST);
	token = parser->token;
	if (token->type != TOKEN_ID && !is_redir(token))
		return (free_tree(ast), parser_syntax_error(token->value), NULL);
	while (token->type == TOKEN_ID || \
	is_redir(token))
	{
		if (!parser_parse_list_inter(token, ast, parser))
			return (NULL);
		token = parser->token;
	}
	if (token->type == TOKEN_LPAREN)
	{
		parser_parser_advance(parser, TOKEN_LPAREN);
		return (free_tree(ast), \
		parser_syntax_error(parser->token->value), NULL);
	}
	return (ast);
}
