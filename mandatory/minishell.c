/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/19 03:34:16 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/global.h"
#include "inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
	createclone(&(g_global.env), envp);
	createclone(&(g_global.exp), envp);
	g_global.envp = envp;
	//g_global.lvl = 0;
	//rl_newline(0,0);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, SIG_IGN);
	//signal(SIGINT, SIG_DFL);
	//signal(, SIG_IGN);
	
	
	//showexport();
	init_minishell();
	return (0);
}

void	init_minishell()
{
	char	*str;

	while (1)
	{
		signal(SIGINT, signal_init);
		
		g_global.interupted = 0;
		str = readline("minishell-👌: ");
		if (!str)
		{
			if (g_global.exit_code == 130)
				ft_putstr_fd("exit", 1);
			else
				ft_putstr_fd("exit\n", 1);
			
			//if (g_global.exit_code != 1 && g_global.prev_exit_code != 1)
			//printf("%d",g_global.exit_code);
			//g_global.prev_exit_code = 0;
			//g_global.exit_code = 0;
			//if (g_global.did_interupt == 0 )
			//	if ()
			exit(g_global.exit_code);
		}
		if (str[0])
		{
			add_history(str);
			g_global.exit_code = 0;
			g_global.fd_error = 0;
			g_global.here_docs = NULL;
			signal(SIGINT, SIG_IGN);
			before_exec(str, g_global.env);
			//printf("{{%d}}%s\n", g_global.exit_code, str);
			if (g_global.interupted && g_global.exit_code == 2)
				g_global.exit_code = 130;
			//if (g_global.interupted && g_global.exit_code == 0)
			//	write(1, "\n", 1);
			//printf("{{%d}}%s\n", g_global.exit_code, str);
			if (g_global.exit_code == 130)
			{
				write(1, "\n", 1);
			}
			g_global.prev_exit_code = g_global.exit_code;
		}
		free(str);
	}
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
	if (g_global.exit_code == 0 && parser->token->type != TOKEN_EOF)
		parser_syntax_error(parser->token->value);
	loop_heredoc();
	if (g_global.exit_code != 0)
	{
		ft_d_lstclear(&(g_global.here_docs), &free_heredoc);
		free_all(lexer, parser, ast, NULL);
		return ;
	}
	builder = builder_build(ast, envp);
	signal(SIGINT, signal_ign);
	ft_d_lstclear(&(g_global.here_docs), &free_heredoc);
	iter_builder(builder);
	g_global.exit_code = ((t_builder *)(ft_d_lstlast(builder)->content))->status;
	if (WIFEXITED(g_global.exit_code))
   		g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	free_all(lexer, parser, ast, builder);
}

void	free_heredoc(void *c)
{
	close(((t_heredoc *)c)->fd[1]);
	if (g_global.exit_code == 258 || g_global.exit_code == 1)
		close(((t_heredoc *)c)->fd[0]);
	free(((t_heredoc *)c)->str);
	free(c);
}

void	free_all(t_lexer *lexer, t_parser *parser, t_ast *ast, \
t_d_list *builder)
{
	if (builder)
		builder_free_builder(builder);
	if (ast)
		free_tree(ast);
	ft_d_lstclear(&(lexer->tokens), free_token);
	if (lexer)
		free(lexer);
	if (parser)
		free(parser);
}

int	loop_heredoc()
{
	t_d_list	*tmp;
	int			id;
	char		*str[3];
	int			status;

	tmp = g_global.here_docs;
	while (tmp)
	{
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, signal_ign2);
			str[2] = ((t_heredoc *)tmp->content)->str;
			str[0] = readline(">");
			while (!str[0] || ft_strncmp(str[2] , str[0], ft_strlen(str[2])))
			{
				str[1] = ft_strjoin(str[0], "\n");
				ft_putstr_fd(str[1], ((t_heredoc *)tmp->content)->fd[1]);
				free(str[0]);
				free(str[1]);
				str[0]= readline(">");
			}
			free(str[0]);
			close(((t_heredoc *)tmp->content)->fd[1]);
			close(((t_heredoc *)tmp->content)->fd[0]);
			exit(0);
		}
		waitpid(id, &status, 0);
		status = WEXITSTATUS(status);
		if (status == 2)
		{
			g_global.exit_code = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}