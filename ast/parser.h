/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 12:23:32 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# include "./lexer.h"
# include "./token.h"
# include "./ast.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*token;
}			t_parser;

t_parser	*init_parser(t_lexer *lexer);
t_token		*parser_advance(t_parser *parser);
t_ast		*parse(t_parser *parser);
t_ast		*parse_text(t_parser *parser);
t_ast		*parse_string(t_parser *parser);
//t_ast		*parse_(t_parser *parser);
//t_ast		*parse(t_parser *parser);

#endif
