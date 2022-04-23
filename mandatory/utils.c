/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:45:09 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 21:12:35 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	free_heredoc(void *c)
{
	close(((t_heredoc *)c)->fd[1]);
	if (g_global.exit_code == 258 || g_global.exit_code == 1)
		close(((t_heredoc *)c)->fd[0]);
	free(((t_heredoc *)c)->str);
	free(c);
}

void	free_all(t_lexer *lexer, t_parser *parser, t_ast *ast, \
t_d_list *builder)
{
	if (builder)
		builder_free_builder(builder);
	if (ast)
		free_tree(ast);
	ft_d_lstclear(&(lexer->tokens), free_token);
	if (lexer)
		free(lexer);
	if (parser)
		free(parser);
}

static	void	here_doc_inter(char **str, t_d_list *tmp)
{
	signal(SIGINT, signal_ign2);
	str[2] = ((t_heredoc *)tmp->content)->str;
	str[0] = readline(">");
	while (!str[0] || ft_strncmp(str[2], str[0], ft_strlen(str[2]) + 1))
	{
		if (!str[0])
			break ;
		str[1] = ft_strjoin(str[0], "\n");
		ft_putstr_fd(str[1], ((t_heredoc *)tmp->content)->fd[1]);
		free(str[0]);
		free(str[1]);
		str[0] = readline(">");
	}
	free(str[0]);
	close(((t_heredoc *)tmp->content)->fd[1]);
	close(((t_heredoc *)tmp->content)->fd[0]);
	exit(0);
}

int	loop_heredoc(void)
{
	t_d_list	*tmp;
	int			id;
	char		*str[3];
	int			status;

	tmp = g_global.here_docs;
	while (tmp)
	{
		id = fork();
		if (id == 0)
			here_doc_inter(str, tmp);
		waitpid(id, &status, 0);
		status = WEXITSTATUS(status);
		if (status == 2)
		{
			g_global.exit_code = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
