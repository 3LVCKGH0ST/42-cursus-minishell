/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 10:18:59 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->token = get_next_token(lexer);
	return (parser);
}

t_token		*parser_eat(t_parser *parser, int type)
{
	if (parser->token->type == type)
	{
		printf("[Parser]: Unexpected token near %s\n", parser->token->value);
		exit(1);
	}
	return (parser->token);
}

t_ast *parse(t_parser *parser)
{
	return (NULL);
}
