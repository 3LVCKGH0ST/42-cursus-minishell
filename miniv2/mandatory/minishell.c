/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/06 23:36:49 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./inc/global.h"
# include "inc/minishell.h"
//# include "./parsing/inc/token.h"
void	before_exec(char *str, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char *str;

	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell-0.0👌");
		if (str && str[0])
			before_exec(str, envp);
		free(str);
	}
	//system("leaks minishell");
	return (0);
}

void	before_exec(char *str, char **envp)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	//t_d_list	*builder;

	g_global.exit_code = 0;
	(void)envp;

	lexer = lexer_init_lexer(str);
	parser = parser_init_parser(lexer);
	if (!parser)
		return ;
	ast = parser_parse(parser);
	if (g_global.exit_code == 0 && parser->token->type != TOKEN_EOF)
	{
		parser_syntax_error(parser->token->value);
		g_global.exit_code = EXIT_SYNTAX_ERROR;
		return ;
	}
	if (g_global.exit_code != 0)
		return ;
	print_tree(ast);
	//parser_parser_advance(parser, TOKEN_EOF);//? needed to hundle this "sadas asd )" unclosed parenthis
	//builder = builder_build(ast);
	//print_builder(builder);
	//t_token		*token;
	//token = lexer_next_token(lexer);
	//while (token->type != TOKEN_EOF)
	//{
	//	printf("%d   %s\n", token->type,token->value);
	//	token = lexer_next_token(lexer);
	//}
	//printf("%d   \n", g_global.exit_code);
	printf("\n");
}