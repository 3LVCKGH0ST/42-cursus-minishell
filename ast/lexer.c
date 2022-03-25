#include "lexer.h"

//void 	advance_lexer(t_lexer *lexer)
//{
//	while (lexer->c && *lexer->c)
//	{
//		if (*lexer->c == ' ' || *lexer->c == '\t')
//			skip_whitespace_lexer(lexer);
//		else if (*lexer->c == '(')
//			lexer->c++;
//		else if (*lexer->c == ')')
//			lexer->c++;
//		else if (*lexer->c == '|')
//			lexer->c++;
//		else if (*lexer->c == '&')
//			lexer->c++;
//		else if (*lexer->c == '<')
//			lexer->c++;
//		else if (*lexer->c == '>')
//			lexer->c++;
//		else if (*lexer->c == '\'')
//			lexer->c++;
//		else if (*lexer->c == '"')
//			lexer->c++;
//		else
//			break ;
//	}
//}
void	advance_lexer(t_lexer *lexer)
{
	while (lexer->c && *lexer->c)
	{
		if (*lexer->c == ' ' || *lexer->c == '\t')
			skip_whitespace_lexer(lexer);
		else if (*lexer->c == '(')
			lexer->c++;
		else if (*lexer->c == ')')
			lexer->c++;
		else if (*lexer->c == '|')
			lexer->c++;
		else if (*lexer->c == '&')
			lexer->c++;
		else if (*lexer->c == '<')
			lexer->c++;
		else if (*lexer->c == '>')
			lexer->c++;
		else if (*lexer->c == '\'')
			lexer->c++;
		else if (*lexer->c == '"')
			lexer->c++;
		else
			break ;
	}
}

//{
//	while (lexer->c && *lexer->c && *lexer->c != '\n')
//		lexer->c++;
//	if (lexer->c && *lexer->c)
//		lexer->c++;
//}

void	skip_whitespace_lexer(t_lexer *lexer)
{
	while (lexer->c && *lexer->c && *lexer->c == ' ')
		lexer->c++;
	while (lexer->c && *lexer->c && *lexer->c == '\t')
		lexer->c++;
}
//{
//	while (lexer->c && *lexer->c && (*lexer->c == ' ' || *lexer->c == '\t'))
//		lexer->c++;
//}

