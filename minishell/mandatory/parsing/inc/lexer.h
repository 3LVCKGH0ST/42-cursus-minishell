/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:36:35 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 15:17:56 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "../../../libft/libft.h"
# include "../../../double_linked_list/double_linked_list.h"
# include "token.h"

/**
 * @brief 	lexer is used to tokenize the input 
 * 			(iterate over the input && get all the tokens)
 * @param 	src is the input to tokenize
 * @param 	c is the current char
 * @param 	cc is the next char
 * @param 	i is the current index
 * @param 	tokens is the list of tokens (to be free at the end)
 */
typedef struct s_lexer
{
	char		*src;
	char		c;
	char		cc;
	size_t		i;
	t_d_list	*tokens;
}				t_lexer;

t_lexer	*lexer_init_lexer(char *src);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*lexer_collect_id(t_lexer *lexer);
t_token	*lexer_advance_w_token(t_lexer *lexer, t_token *token);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace_lexer(t_lexer *lexer);
char	*to_str(char c);
int		is_reserved_token(char c);
#endif
