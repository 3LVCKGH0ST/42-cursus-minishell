/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/06 02:12:33 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./inc/global.h"
# include "inc/minishell.h"
//# include "./parsing/inc/token.h"

int	main(int argc, char **argv, char **envp)
{
	t_lexer		*lexer;
	//t_parser	*parser;
	//t_ast		*ast;
	//t_d_list	*builder;

	g_global.exit_code = 0;
	//g_env = envp;
	(void)argc;
	(void)argv;
	(void)envp;

	lexer = lexer_init_lexer("'''");
	//parser = parser_init_parser(lexer);
	//ast = parser_parse(parser);
	//parser_parser_advance(parser, TOKEN_EOF);//? needed to hundle this "sadas asd )" unclosed parenthis
	//builder = builder_build(ast);
	//print_builder(builder);
	t_token		*token;
	token = lexer_next_token(lexer);
	while (token->type != TOKEN_EOF)
	{
		printf("%d   %s\n", token->type,token->value);
		token = lexer_next_token(lexer);
	}
	printf("%d   \n", g_global.exit_code);
	ft_d_lstclear(&lexer->tokens, free_token);
	//system("leaks minishell");
	return (0);
}
