/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 09:31:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/29 22:05:10 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->token = get_next_token(lexer);
	return (parser);
}

t_token	*parser_eat(t_parser *parser, t_e_token type)
{ 
	if (parser->token->type != type)
	{
		printf("[Parser]: Unexpected token near %s\n", parser->token->value);
		exit(127);
	}
	parser->token = get_next_token(parser->lexer);
	return (parser->token);
}

t_ast	*parse(t_parser *parser)
{
	if (parser->token->type == TOKEN_LPAREN)
		return (parse_paren(parser));
	if (parser->token->type == TOKEN_EOF)
		return (NULL);
	return (parse_pipeline(parser));
}

t_ast		*parse_text(t_parser *parser)
{
	t_ast	*ast;
	char	*text;

	text = ft_strdup(parser->token->value);
	parser_eat(parser, TOKEN_TEXT);
	if(parser->token->type == TOKEN_TEXT)
	{
		ast = init_ast(AST_LIST);
		ast->value = text;
		return (ast);
	}
	ast = init_ast(AST_LIST);
	ast->value = parser->token->value;
	parser_eat(parser, TOKEN_TEXT);
	return (ast);
}

//t_ast		*parse_text(t_parser *parser)
//{
//	t_ast	*ast;
//	char	*text;

//	text = ft_strdup(parser->token->value);
//	if(parser->token->type == TOKEN_TEXT)
//	{
//		ast = init_ast(AST_TXT);
//		ast->value = text;
//		return (ast);
//	}
//	ast = init_ast(AST_LIST);
//	ast->value = parser->token->value;
//	parser_eat(parser, TOKEN_TEXT);
//	return (ast);
//}

t_ast		*parse_id(t_parser *parser)
{
	t_ast	*ast;
	char	*text;

	text = ft_strdup(parser->token->value);
	if(parser->token->type == TOKEN_ID)
	{
		ast = init_ast(AST_ID);
		ast->value = text;
		return (ast);
	}
	parser_eat(parser, TOKEN_ID);
	return (NULL);
}

t_ast		*parse_quote(t_parser *parser)
{
	t_ast	*ast;

	if(parser->token->type == parser->token->type)
	{
		ast = init_ast(AST_QOUTE);
		ast->type_token = parser->token->type;	
		ast->value = ft_strdup(parser->token->value);
		return (ast);
	}
	parser_eat(parser, parser->token->type);
	return (NULL);
}

t_ast		*parse_redir(t_parser *parser)
{
	t_ast	*ast;

	if(parser->token->type == TOKEN_RIN || parser->token->type == TOKEN_ROUT || parser->token->type == TOKEN_DRIN || parser->token->type == TOKEN_DROUT)
	{
		ast = init_ast(AST_REDIR);
		ast->type_token = parser->token->type;
		parser_eat(parser, parser->token->type);
		if (parser->token->type == TOKEN_ID || parser->token->type == TOKEN_DQUOTE || parser->token->type == TOKEN_SQUOTE)
		{
			//printf("{%s}", parser->token->value);	
			ast->value = ft_strdup(parser->token->value);
		}
		else
		{
			parser_eat(parser, TOKEN_PIPE);
			if (parser->token->type == TOKEN_ID || parser->token->type == TOKEN_DQUOTE || parser->token->type == TOKEN_SQUOTE)
			{
				ast->value = ft_strdup(parser->token->value);
			}
		}
		//parser_eat(parser, parser->token->type);
		return (ast);
	}
	parser_eat(parser, TOKEN_TEXT);
	return (NULL);	
}

t_ast		*parse_list(t_parser *parser)
{
	t_ast	*ast;

	if(parser->token->type == TOKEN_ID || parser->token->type == TOKEN_DQUOTE || parser->token->type == TOKEN_SQUOTE || \
		parser->token->type == TOKEN_RIN || parser->token->type == TOKEN_ROUT || parser->token->type == TOKEN_DRIN || parser->token->type == TOKEN_DROUT
	)
	{
		ast = init_ast(AST_LIST);
		while (parser->token->type == TOKEN_ID || parser->token->type == TOKEN_DQUOTE || parser->token->type == TOKEN_SQUOTE || \
		parser->token->type == TOKEN_RIN || parser->token->type == TOKEN_ROUT || parser->token->type == TOKEN_DRIN || parser->token->type == TOKEN_DROUT)
		{
			if (parser->token->type == TOKEN_ID || parser->token->type == TOKEN_DQUOTE || parser->token->type == TOKEN_SQUOTE)
				if (parser->token->type == TOKEN_ID)
					ft_d_lstadd_back(&(ast->args), ft_d_lstnew(parse_id(parser)));
				else
					ft_d_lstadd_back(&(ast->args), ft_d_lstnew(parse_quote(parser)));
			else
				ft_d_lstadd_back(&(ast->redir), ft_d_lstnew(parse_redir(parser)));
			parser_eat(parser, parser->token->type);
		}
		return (ast);
	}
	//parser_eat(parser, TOKEN_ID);
	return (NULL);
}


void	print_tree_list(t_ast *ast)
{
	t_d_list	*tmp2;

	if (ast && ast->type == AST_LIST)
	{
		tmp2 = ast->args;
		while (tmp2)
		{
			printf(" %s ", ((t_ast *)tmp2->content)->value);
			tmp2 = tmp2->next;
		}
		tmp2 = ast->redir;
		if (tmp2)
			printf("  <>  ");
		while (tmp2)
		{
			printf(" %s ", ((t_ast *)tmp2->content)->value);
			tmp2 = tmp2->next;
		}
	}
}

void	print_tree(t_ast *ast)
{
	if (ast && ast->type == AST_LIST)
		print_tree_list(ast);
	if (ast && ast->type == AST_PIPELINE)
		print_tree_pipline(ast);
	if (ast && ast->type == AST_PAREN)
		print_tree_paren(ast);
}

t_ast		*parse_pipeline(t_parser *parser)
{
	t_ast	*ast;

		ast = init_ast(AST_PIPELINE);
		//print_tree_list((t_ast *)ast2);
		if (parser->token->type == TOKEN_LPAREN)
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse(parser)));
		else
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse_list(parser)));
		while (parser->token->type == TOKEN_PIPE)
		{
			parser_eat(parser, TOKEN_PIPE);
			if (parser->token->type == TOKEN_LPAREN)
				ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse(parser)));
			else
				ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse_list(parser)));
		}
		if (parser->token->type == TOKEN_PIPE)	
			parser_eat(parser, TOKEN_PIPE);
		return (ast);
}

t_ast		*parse_paren(t_parser *parser)
{
	t_ast	*ast;

	if(parser->token->type == TOKEN_LPAREN)
	{
		parser_eat(parser, TOKEN_LPAREN);
		ast = init_ast(AST_PAREN);
		//print_tree_list((t_ast *)ast2);
		ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse(parser)));
		while (parser->token->type == TOKEN_PIPE)
		{
			parser_eat(parser, TOKEN_PIPE);
			ft_d_lstadd_back(&(ast->children), ft_d_lstnew(parse(parser)));
		}
		parser_eat(parser, TOKEN_RPAREN);
		return (ast);
	}
	//parser_eat(parser, TOKEN_PIPE);
	return (NULL);
}

void	print_tree_pipline(t_ast *ast)
{
	t_d_list	*tmp2;

	if (ast && ast->type == AST_PIPELINE)
	{
		tmp2 = ast->children;
		while (tmp2)
		{
			print_tree((t_ast *)tmp2->content);
			printf("\n");
			tmp2 = tmp2->next;
		}
	}
}

void	print_tree_paren(t_ast *ast)
{
	t_d_list	*tmp2;

	if (ast && ast->type == AST_PAREN)
	{
		tmp2 = ast->children;
		while (tmp2)
		{
			printf("\n------\n");
			print_tree((t_ast *)tmp2->content);
			printf("\n------\n");
			tmp2 = tmp2->next;
		}
	}
}