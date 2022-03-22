/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:39 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 13:40:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkpipes(char	*str)
{
	int	i;

	i = skiprtspace(str);
	if (str && str[i] == '|')
		return (1);
	return (0);
}

/*
checkheredoc returns value :
- -1	:	parsing error
-  0	:	<< not found
-  1	:	0 errors
*/

int	checkheredoc(char *str)
{
	int	i;
	int	returnval;

	i = skiplfspace(str, 0);
	returnval = 0;
	if (str && str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		i = skiplfspace(str, i);
		while (str && str[i])
		{
			if (str && (str[i] == '<' || str[i] == '>'))
				return (-1);
			printf("%c", str[i]);
			i++;
		}
		returnval = 1;
	}
	return (returnval);
}
/**
 * @brief checks the end and start of line if it starts or ends with pipe return 0
 * 
 * @param line the line read from prompt
 * @return int 0 if pipe in end or start and 1 if line start with anything other than pipe |
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

void	readinputs(char **read)
{
	char	*str;
	//char	**cmds;
	//int		i;
	//int		*pipes;
	str = *read;
	while (1)
	{
		str = readline("minishell$ : ");
		printf("=> %s\n", str);
		
		printf("pipe checker %d\n", check_end_start_pipes(str));
		printf("quote checker %d\n", quotescheckers(str,  ft_strlen(str)));
		//printf("here_doc checker %d\n", checkheredoc(str));
		//cmds = split_cmds(str);
		//quotescheckers(str);
		//pipes = get_pipe_idxs(str);
		//i = -1;
		//int	dupft[2];
		//dupft[0] = 0;
		////printf("|||%s\n", 	ft_strdup_v2(str, 0,4));
		//while (pipes[++i] > 0)
		//{
		//	//printf("--%d--\n", pipes[i]);
		//	dupft[1] = pipes[i] - 1;
		//	//printf("--%d*%d--\n", dupft[0], dupft[1]);
		//	//0123|5678
		//	printf("%s\n", 	ft_strdup_v2(str, dupft[0],dupft[1]));
		//	dupft[0] = pipes[i] + 1;
		//}
		//dupft[1] = ft_strlen(str) - 1;
		//if (dupft[1] < 0)
		//	dupft[1] = 0;
		////printf("--%d*%d--\n", dupft[0], dupft[1]);
		//printf("%s\n", 	ft_strdup_v2(str, dupft[0], dupft[1]));
		//printf("%s\n", 	ft_strdup_v2(str,0,pipes[1]));
		free(str);
		//i = 0;
		//while (cmds && cmds[++i])
		//{
		//	printf("\t%s\n", cmds[i]);			
		//}
	}
}

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

char **split_cmds(char *line)
{
	int	*pipes;
	int	i;
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
	//fill_piped_parts(pipes, );
	return (NULL);
}
