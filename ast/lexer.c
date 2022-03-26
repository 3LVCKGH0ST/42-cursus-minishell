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


t_token	*get_next_token(t_lexer *lexer)
{
	t_token	*token;

	skip_whitespace_lexer(lexer);
	if (!lexer->c || !*lexer->c)
		return (NULL);
	if (*lexer->c == '(')
	{
		token = init_token("(", TOKEN_LPAREN);
		lexer->c++;
	}
	else if (*lexer->c == ')')
	{
		token = init_token(")", TOKEN_RPAREN);
		lexer->c++;
	}
	else if (*lexer->c == '|' && *(lexer->c + 1) == '|')
	{
		token = init_token("||", TOKEN_OR);
		lexer->c++;
	}
	else if (*lexer->c == '|')
	{
		token = init_token("|", TOKEN_PIPE);
		lexer->c++;
	}
	else if (*lexer->c == '&' && *(lexer->c + 1) == '&')
	{
		token = init_token("&&", TOKEN_AND);
		lexer->c++;
	}
	else if (*lexer->c == '<' && *(lexer->c + 1) == '<')
	{
		token = init_token("<<", TOKEN_RIN);
		lexer->c++;
	}
	else if (*lexer->c == '<')
	{
		token = init_token("<", TOKEN_RIN);
		lexer->c++;
	}
	else if (*lexer->c == '>' && *(lexer->c + 1) == '>')
	{
		token = init_token(">>", TOKEN_ROUT);
		lexer->c++;
	}
	else if (*lexer->c == '>')
	{
		token = init_token(">", TOKEN_ROUT);
		lexer->c++;
	}
	else if (*lexer->c == '\'')
	{
		token = init_token("'", TOKEN_SQUOTE);
		lexer->c++;
	}
	else if (*lexer->c == '"')
	{
		token = init_token("\"", TOKEN_DQUOTE);
		lexer->c++;
	}
	else
	{
		token = init_token(lexer->c, TOKEN_TEXT);
		while (lexer->c && *lexer->c && *lexer->c != ' ' && *lexer->c != '\t' && *lexer->c != '\n')
			lexer->c++;
	}
	return (token);
}
t_token	*collect_string(t_lexer *lexer)
{
	t_token	*token;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (*lexer->c == '\'')
	{
		lexer->c++;
		while (lexer->c && *lexer->c && *lexer->c != '\'')
		{
			str = ft_strjoin(str, ft_strdup(lexer->c));
			lexer->c++;
		}
		if (lexer->c && *lexer->c)
			lexer->c++;
		token = init_token(str, TOKEN_SQUOTE);
	}
	else if (*lexer->c == '"')
	{
		lexer->c++;
		while (lexer->c && *lexer->c && *lexer->c != '"')
		{
			str = ft_strjoin(str, ft_strdup(lexer->c));
			lexer->c++;
		}
		if (lexer->c && *lexer->c)
			lexer->c++;
		token = init_token(str, TOKEN_DQUOTE);
	}
	return (token);
}

t_token	*collect_text(t_lexer *lexer)
{
	t_token	*token;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (lexer->c && *lexer->c && *lexer->c != ' ' && *lexer->c != '\t' && *lexer->c != '\n')
	{
		str = ft_strjoin(str, ft_strdup(lexer->c));
		lexer->c++;
	}
	token = init_token(str, TOKEN_TEXT);
	return (token);
}