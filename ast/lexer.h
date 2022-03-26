#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "../libft/libft.h"
# include "./token.h"

typedef struct s_lexer
{
	char	*src;
	int		i;
}	 t_lexer;

t_lexer	init_lexer(char *src);
void 	advance_lexer(t_lexer *lexer);
void	skip_whitespace_lexer(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*collect_quoted_string(t_lexer *lexer);
t_token	*collect_text(t_lexer *lexer);
char 	*to_string(char c);
//t_token	*collect_text(t_lexer *lexer);
//t_token	*collect_token(t_lexer *lexer);

#endif
