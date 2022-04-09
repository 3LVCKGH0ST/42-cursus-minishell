/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:57:51 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/09 03:40:29 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	execute(t_d_list *node)
{
	if (open_in_files(node))
		printf("execute  %s\n", ( (t_builder *)node->content)->cmd->args[0]);
}

int	open_in_files(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;
	char		*tmp_str;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_RIN)
		{
			redir_tmp->fd = open(redir_tmp->file, O_RDONLY);
			if (redir_tmp->fd < 0)
			{
				tmp_str = ft_strjoin("minishell: ", redir_tmp->file);
				perror(tmp_str);
				return (free(tmp_str), 0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	open_out_files(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;
	char		*tmp_str;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_ROUT)
			redir_tmp->fd = open(redir_tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			redir_tmp->fd = open(redir_tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir_tmp->fd < 0)
		{
			tmp_str = ft_strjoin("minishell: ", redir_tmp->file);
			perror(tmp_str);
			return (free(tmp_str), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_d_list	*here_doc_limiters(t_d_list *node)
{
	t_d_list	*tmp;
	t_redir		*redir_tmp;
	t_d_list	*here_doc_limiters;

	tmp = ((t_builder *)node->content)->cmd->redir_in;
	here_doc_limiters = NULL;
	while (tmp)
	{
		redir_tmp = tmp->content;
		if (redir_tmp->type == TOKEN_DRIN)
			ft_d_lstadd_back(&here_doc_limiters, ft_d_lstnew(redir_tmp->file));
		tmp = tmp->next;
	}
	return (here_doc_limiters);
}

int	here_doc_check(t_d_list *lims, t_d_list *stack)
{
	(void)stack;
	(void)lims;
	return (1);
}

int		open_here_doc(t_d_list *node)
{
	t_d_list	*lims;
	t_d_list	*stack;
	char		*str;
	int			fd[2];

	lims = here_doc_limiters(node);
	if (!lims || pipe(fd) < 0)
		return (-1);
	str = readline(">");
	ft_d_lstadd_back(&stack, ft_d_lstnew(str));
	while (here_doc_check(lims, stack))
	{
		ft_putstr_fd(str, fd[1]);
		str = readline(">");
		ft_d_lstadd_back(&stack, ft_d_lstnew(str));
	}
	ft_d_lstclear(&stack, &free);
	close(fd[1]);
	return (fd[0]);
}
