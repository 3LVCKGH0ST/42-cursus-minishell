/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/27 10:06:49 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../libft/libft.h"
# include "./lexer.h"


typedef struct	s_parser
{
	t_lexer			*lexer;
	t_token			*token;
}			t_parser;

t_parser	*init_parser(t_lexer *lexer);
t_token		*parser_advance(t_parser *parser);
t_ast *parse(t_parser *parser);
#endif
