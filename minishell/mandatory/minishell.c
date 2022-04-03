/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/03 13:07:33 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//# include "./parsing/inc/token.h"

int	main(int argc, char **argv)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_d_list	*builder;

	(void)argc;
	(void)argv;
	lexer = lexer_init_lexer("\"ls\" '||' cat >s | ((wc || ss) && sss) ");
	parser = parser_init_parser(lexer);
	ast = parser_parse(parser);
	builder = builder_build(ast);
	print_builder(builder);
	ft_d_lstclear(&lexer->tokens, free_token);
	//system("leaks minishell");
	return (0);
}
