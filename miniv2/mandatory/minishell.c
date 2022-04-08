/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/08 17:14:48 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/global.h"
#include "inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell-0.0👌");
		if (str && str[0])
			before_exec(str, envp);
		printf("\n");
		free(str);
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

	g_global.exit_code = 0;
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
		return ;
	}
	builder = builder_build(ast, envp);
	print_builder(builder);
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
