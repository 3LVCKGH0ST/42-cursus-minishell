#include "lexer.h"
#include "parser.h"

int	main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	t_lexer	*lexer;
	t_parser	*parser;
	t_ast	*ast;
	lexer = init_lexer(" (ls) || cat >s | ((wc || ss) && sss) ");
	parser = init_parser(lexer);
	ast = parse_pipeline(parser);
	print_tree(ast);
	return (0);
}