/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 20:12:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "./lexer.h"
# include "../../../libft/libft.h"
# include "./ast.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*token;
}			t_parser;

t_parser	*parser_init_parser(t_lexer *lexer);
t_token		*parser_parser_advance(t_parser *parser, t_e_token type);
t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_id(t_parser *parser);
t_ast		*parser_parse_redir(t_parser *parser);
t_ast		*parser_parse_list(t_parser *parser);
t_ast		*parser_parse_pipeline(t_parser *parser);
t_ast		*parser_parse_term(t_parser *parser);
t_ast		*parser_parse_paren(t_parser *parser);
void		parser_syntax_error(char *token_value);
int			is_redir(t_token *token);
#endif
