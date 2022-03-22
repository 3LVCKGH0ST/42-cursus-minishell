/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:15:48 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/22 19:03:01 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/**
 * @brief Get the pipe idxs list to parse line with it
 * 
 * @param line line from prompt
 * @return int* array of pipes indexs (not in quotes) followed by value -1
 */
int	*get_pipe_idxs(char *line)
{
	int	*pipes;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line && line[++i])
		if (line[i] == '|' && !quotescheckers(line, i))
			j++;
	pipes = malloc(sizeof(int) * (j + 1));
	if (!pipes)
		return (NULL);
	pipes[j] = -1;
	i = -1;
	j = 0;
	while (line && line[++i])
		if (line[i] == '|' && !quotescheckers(line, i))
			pipes[j++] = i;
	return (pipes);
}

/**
 * @brief copies strings to cmds array using pipes idxs
 * 
 * @param pipes 
 * @param cmds 
 * @param line 
 */
static void	fill_piped_parts(int *pipes, char **cmds, char *line)
{
	int	dupft[2];
	int	i;
	int	j;

	j = -1;
	i = -1;
	dupft[0] = 0;
	while (pipes[++i] > 0)
	{
		dupft[1] = pipes[i] - 1;
		cmds[++j] = ft_strdup_v2(line, dupft[0], dupft[1]);
		dupft[0] = pipes[i] + 1;
	}
	dupft[1] = ft_strlen(line) - 1;
	if (dupft[1] < 0)
		dupft[1] = 0;
	cmds[++j] = ft_strdup_v2(line, dupft[0], dupft[1]);
}

/**
 * @brief take line and split it with pipes outside quotes
 * 
 * @param line 
 * @return char** NULL or array of char * ended with NULL
 */
char	**split_cmds(char *line)
{
	int		*pipes;
	int		i;
	char	**cmds;

	pipes = get_pipe_idxs(line);
	if (!pipes)
		return (NULL);
	i = -1;
	while (pipes[++i] >= 0)
		;
	cmds = malloc(sizeof(char *) * (i + 2));
	cmds[i + 1] = NULL;
	if (!cmds)
		return (NULL);
	fill_piped_parts(pipes, cmds, line);
	return (cmds);
}

/**
 * @brief checks the end and start of line if
 *  it starts or ends with pipe return 0
 * 
 * @param line the line read from prompt
 * @return int 0 if pipe in end or start and 1 if line start
 * 			 with anything other than pipe |
 */
int	check_end_start_pipes(char *line)
{
	int	s;

	s = 0;
	while (line && line[s] && line[s] == ' ')
		++s;
	if (line && line[s] == '|')
		return (0);
	s = ft_strlen(line);
	if (s == 0)
		return (1);
	s--;
	while (line && line[s] && line[s] == ' ')
		--s;
	if (line && line[s] == '|')
		return (0);
	return (1);
}
