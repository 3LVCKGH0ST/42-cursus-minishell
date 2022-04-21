/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:31:54 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/global_bonus.h"
#include "inc/minishell_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	createclone(&(g_global.env), envp);
	createclone(&(g_global.exp), envp);
	g_global.envp = envp;
	signal(SIGQUIT, SIG_IGN);
	init_minishell();
	return (0);
}

static void	init_minishell_inter(char *str)
{
	add_history(str);
	g_global.exit_code = 0;
	g_global.fd_error = 0;
	g_global.here_docs = NULL;
	signal(SIGINT, SIG_IGN);
	before_exec(str, g_global.env);
	if (g_global.interupted && g_global.exit_code == 2)
		g_global.exit_code = 130;
	if (g_global.exit_code == 130 \
	&& !(!ft_strncmp(str, "./minishell", 12) || \
		!ft_strncmp(str, "./minishell ", 13)))
	{
		write(1, "\n", 1);
	}
	if (g_global.exit_code == 3)
	{
		if (!(!ft_strncmp(str, "./minishell", 12) || \
		!ft_strncmp(str, "./minishell ", 13)))
			printf("Quit: %d\n", g_global.exit_code);
		g_global.exit_code = 131;
	}
	g_global.prev_exit_code = g_global.exit_code;
}

void	init_minishell(void)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, signal_init);
		g_global.interupted = 0;
		g_global.quited = 0;
		str = readline("minishell-bonus-👌: ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 1);
			exit(g_global.exit_code);
		}
		if (str[0])
			init_minishell_inter(str);
		free(str);
	}
}

static int	before_exec_inter(t_lexer *lexer, t_parser *parser, t_ast *ast)
{
	if (g_global.exit_code == 0 && parser->token->type != TOKEN_EOF)
		parser_syntax_error(parser->token->value);
	loop_heredoc();
	if (g_global.exit_code != 0)
	{
		ft_d_lstclear(&(g_global.here_docs), &free_heredoc);
		free_all(lexer, parser, ast, NULL);
		return (0);
	}
	return (1);
}

void	before_exec(char *str, char **envp)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_d_list	*builder;

	lexer = lexer_init_lexer(str);
	if (!lexer)
		return ;
	parser = parser_init_parser(lexer);
	if (!parser)
		return ;
	ast = parser_parse(parser);
	if (!before_exec_inter(lexer, parser, ast))
		return ;
	builder = builder_build(ast, envp);
	signal(SIGINT, signal_ign);
	ft_d_lstclear(&(g_global.here_docs), &free_heredoc);
	iter_builder(builder);
	g_global.exit_code = \
	((t_builder *)(ft_d_lstlast(builder)->content))->status;
	if (WIFEXITED(g_global.exit_code))
		g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	free_all(lexer, parser, ast, builder);
}
