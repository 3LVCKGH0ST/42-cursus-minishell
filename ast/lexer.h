#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "../libft/libft.h"
# include "./token.h"

typedef struct s_lexer
{
	char	*src;
	size_t	src_size;
	char	*c;
}	 t_lexer;

t_lexer	init_lexer(char *src);
t_token	*lexer(t_lexer *lexer);
void 	advance_lexer(t_lexer *lexer);
void	skip_whitespace_lexer(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
#endif
