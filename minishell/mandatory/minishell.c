/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/03 17:51:13 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	run_minishell(char *str, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell👌: ");
		//printf("\n");
		if (str && *str)
		{
			run_minishell(str, envp);
			printf("\n");
		}
	}
	//system("leaks minishell");
	return (0);
}

void	run_minishell(char *str, char **envp)
{		
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_d_list	*builder;

	lexer = lexer_init_lexer(str);
	parser = parser_init_parser(lexer);
	ast = parser_parse(parser);
	//if (!ast)
	//	parser_parser_advance(parser, TOKEN_EOF);//? needed to hundle this "sadas asd )" unclosed parenthis
	builder = builder_build(ast, envp);
	print_builder(builder);
}
