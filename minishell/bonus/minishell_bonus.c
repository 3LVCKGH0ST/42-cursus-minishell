/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/30 18:00:08 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

# include "./parsing/parser_bonus.h"

int	main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_lexer	*lexer;
	t_parser	*parser;
	t_ast	*ast;
	lexer = init_lexer(" '\"ssssss\"' ");
	parser = init_parser(lexer);
	ast = parse_pipeline(parser);
	print_tree(ast);
	return (0);
}
