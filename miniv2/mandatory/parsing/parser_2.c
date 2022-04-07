/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:41:54 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/07 02:03:47 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"	

void	parser_syntax_error(char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
	g_global.exit_code = EXIT_SYNTAX_ERROR;
}

int	is_redir(t_token *token)
{
	if (token->type == TOKEN_RIN)
		return (1);
	else if (token->type == TOKEN_DRIN)
		return (1);
	else if (token->type == TOKEN_ROUT)
		return (1);
	else if (token->type == TOKEN_DROUT)
		return (1);
	else
		return (0);
}

int	is_op(t_token *token)
{
	if (token->type == TOKEN_AND)
		return (1);
	else if (token->type == TOKEN_OR)
		return (1);
	else
		return (0);
}
