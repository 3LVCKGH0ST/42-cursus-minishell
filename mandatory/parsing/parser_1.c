/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:43:29 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/20 22:08:21 by asouinia         ###   ########.fr       */
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

int	here_doc(char *limiter)
{
	int			fd[2];
	t_heredoc	*here_doc_;

	if (pipe(fd) < 0)
	{
		g_global.fd_error = errno;
		g_global.fd_file_error = "";
		return (-1);
	}
	here_doc_ = malloc(sizeof(t_heredoc));
	if (!here_doc_)
		return (-1);
	here_doc_->fd[1] = fd[1];
	here_doc_->fd[0] = fd[0];
	here_doc_->str = ft_strdup(limiter);
	ft_d_lstadd_back(&g_global.here_docs, ft_d_lstnew(here_doc_));
	return (fd[0]);
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
		return (free_tree(ast), NULL);
	if (!g_global.fd_error && token->type != TOKEN_DRIN)
	{
		if (token->type == TOKEN_RIN)
		{
			if (access(ast->child->value, F_OK) \
			|| access(ast->child->value, R_OK))
			{
				g_global.fd_error = errno;
				g_global.fd_file_error = ast->child->value;
			}
			else
				ast->fd = open(ast->child->value, O_RDONLY);
		}
		else
		{
			if (token->type == TOKEN_RIN && (access(ast->child->value, F_OK) \
			|| access(ast->child->value, W_OK)))
			{
				g_global.fd_error = errno;
				g_global.fd_file_error = ast->child->value;
			}
			else if (token->type == TOKEN_ROUT)
				ast->fd = open(ast->child->value, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (token->type == TOKEN_DROUT)
				ast->fd = open(ast->child->value, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
	}
	else if (token->type == TOKEN_DRIN)
		ast->fd = here_doc(ast->child->value);
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
		return (free_tree(ast), parser_syntax_error(token->value), NULL);
	while (token->type == TOKEN_ID || \
	is_redir(token))
	{
		if (token->type == TOKEN_ID)
		{
			tmp = parser_parse_id(parser);
			if (!tmp)
				return (free_tree(ast), NULL);
			ft_d_lstadd_back(&(ast->args), ft_d_lstnew(tmp));
		}
		else
		{
			tmp = parser_parse_redir(parser);
			if (!tmp)
				return (free_tree(ast), NULL);
			ft_d_lstadd_back(&(ast->redir), ft_d_lstnew(tmp));
		}
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
