/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/12 20:49:31 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/global.h"
#include "inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	g_global.env = envp;
	//signal(SIGUSR1, signal_history);
	//signal(SIGUSR2, signal_history);
	while (1)
	{
		g_global.exit_code = 0;
		g_global.fd_error = 0;
		str = readline("minishell-👌: ");
		if (!str)
			return (0);
		if (str[0])
		{
			add_history(str);
			before_exec(str, envp);
		}
		g_global.prev_exit_code = g_global.exit_code;
		free(str);
		//system("leaks minishell");
	}
	return (0);
}
//void	f(void *s)
//{
//	printf("%s\n", ((t_token *)s)->value);
//}

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
	if (g_global.exit_code != 0)
	{
		free_all(lexer, parser, ast, NULL);
		//fprintf(stderr, "test\n");
		//fprintf(stdout, "test\n");
		return ;
	}
	builder = builder_build(ast, envp);
	//print_builder(builder);
	//printf("\n");
	iter_builder(builder);
	g_global.exit_code = ((t_builder *)(ft_d_lstlast(builder)->content))->status;
	//printf("{}{}{%d}\n",((t_builder *)(ft_d_lstlast(builder)->content))->status % 255);
	 if (WIFEXITED(g_global.exit_code))
        g_global.exit_code = WEXITSTATUS(g_global.exit_code);
	//free_all(lexer, parser, ast, NULL);
	free_all(lexer, parser, ast, builder);
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
