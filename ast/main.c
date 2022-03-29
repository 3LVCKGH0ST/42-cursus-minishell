#include "lexer.h"
#include "parser.h"

int	main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_lexer	*lexer;
	//t_token	*token;
	t_parser	*parser;
	t_ast	*ast;
	lexer = init_lexer(" (ls) | cat >s | wc | sss ");
	parser = init_parser(lexer);
	ast = parse_pipeline(parser);
	print_tree(ast);
	//printf("%p\n",ast);
	//printf("|||||   %d   |||\n", ft_isalnum('<'));
	//token = collect_id(lexer);
	//printf("{\t%d\t|\t%s\t}\n", token->type, token->value);
	//token = get_next_token(lexer);
	//while ( token->type != TOKEN_EOF )
	//{
		//printf("{\t%d\t|\t%s\t}\n", token->type, token->value);
		//token = get_next_token(lexer);
	//}
	//printf("sheeeesh");
	return (0);
}