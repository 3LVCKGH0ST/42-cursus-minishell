/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 21:32:41 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//# include "./parsing/inc/token.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	//t_token		*token;
	lexer = lexer_init_lexer("echo \"Hello World\" ");
	//lexer = lexer_init_lexer("(\"ls\") '||' cat >s | ((wc || ss) && sss) ");
	//lexer = lexer_init_lexer("'");
	parser = parser_init_parser(lexer);
	ast = parser_parse(parser);
	t_d_list	*builder;

	builder = get_tree_builder(ast);
	print_builder(builder);
	//print_tree(ast);
	//printf("\n");
	//token = lexer_next_token(lexer);
	//while (token->type != TOKEN_EOF)
	//{
	//	printf(" %d  %s   \n", token->type, token->value);
	//	token = lexer_next_token(lexer);
	//}
	ft_d_lstclear(&lexer->tokens, free_token);
	//while (1)
	//{
	//	/* code */
	//}
	
	return (0);
}
