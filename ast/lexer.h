#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include "./token.h"

typedef struct s_lexer
{
	char	*src;
	size_t	src_size;
	char	*c;
}	 t_lexer;



#endif
