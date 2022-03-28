/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/28 21:10:00 by asouinia         ###   ########.fr       */
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
//t_ast		*parse_(t_parser *parser);
//t_ast		*parse(t_parser *parser);


t_ast		*parse_text(t_parser *parser);
t_ast		*parse_string(t_parser *parser);

t_ast		*parse_arg(t_parser *parser);
t_ast		*parse_redir(t_parser *parser);
t_ast		*parse_list(t_parser *parser);
t_ast		*parse_pipeline(t_parser *parser);
t_ast		*parse_op(t_parser *parser);
t_ast		*parse_paren(t_parser *parser);




#endif
