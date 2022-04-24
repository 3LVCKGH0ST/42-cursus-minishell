/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:34:10 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/execute.h"

int	skiplfspace(char *str, int index)
{
	while (str && str[index] == ' ')
		index++;
	return (index);
}

int	skiprtspace(char *str)
{
	int	index;

	index = ft_strlen(str) - 1;
	if (index < 0)
		return (0);
	while (str && str[index] == ' ')
		index--;
	return (index);
}

void	print_error_fd(t_d_list	*node)
{
	char	*tmp;

	if (((t_builder *)node->content)->fd_error == -1)
	{
		write(2, "minishell: ", 12);
		write(2, ((t_builder *)node->content)->fd_file_error, \
		ft_strlen(((t_builder *)node->content)->fd_file_error));
		write(2, ": ambiguous redirect\n", 22);
		g_global.exit_code = 1;
	}
	else if (((t_builder *)node->content)->fd_error)
	{
		errno = ((t_builder *)node->content)->fd_error;
		tmp = ft_strjoin("minishell: ", \
		((t_builder *)node->content)->fd_file_error);
		perror(tmp);
		free(tmp);
		g_global.exit_code = 1;
	}
}
