/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/31 18:48:22 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//# include "./parsing/inc/token.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_lexer		*lexer;
	//t_parser	*parser;
	//t_ast		*ast;
	t_token		*token;
	lexer = lexer_init_lexer(" (ls) || cat >s | ((wc || ss) && sss) ");
	//lexer = lexer_init_lexer("(\"ls\") '||' cat >s | ((wc || ss) && sss) ");
	//lexer = lexer_init_lexer("ssss \"aaalol & sss 'ss'");
	//parser = init_parser(lexer);
	//ast = parse_pipeline(parser);
	//print_tree(ast);
	token = lexer_next_token(lexer);
	while (token->type != TOKEN_EOF)
	{
		printf(" %d  %s   \n", token->type, token->value);
		token = lexer_next_token(lexer);
	}
	ft_d_lstclear(&lexer->tokens, free_token);
	while (1)
	{
		/* code */
	}
	
	return (0);
}
