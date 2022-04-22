/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:49:46 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 05:55:41 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

static void	redir_open_files_inter(t_token *token, t_ast *ast)
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

static void	redir_open_files(t_token *token, t_ast *ast)
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
		redir_open_files_inter(token, ast);
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
	if (check_outside_quotes(ast->child->value) && token->type != TOKEN_DRIN)
	{
		g_global.exit_code = 1;
		write(2, "minishell: ", 12);
		write(2, ast->child->value, ft_strlen(ast->child->value));
		write(2, ": ambiguous redirect\n", 22);
	}
	if (!g_global.fd_error && token->type != TOKEN_DRIN)
		redir_open_files(token, ast);
	else if (token->type == TOKEN_DRIN)
		ast->fd = here_doc(ast->child->value);
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
