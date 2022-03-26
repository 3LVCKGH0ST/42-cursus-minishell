#include "lexer.h"

int	main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer("'hello '|'world' (' <<' ff)");
	//printf("%s\n", lexer->src);
	token = get_next_token(lexer);
	while ( token->type != TOKEN_EOF )
	{
		printf("{%d|%s}\n", token->type, token->value);
		token = get_next_token(lexer);
	}
	//printf("sheeeesh");
	return (0);
}