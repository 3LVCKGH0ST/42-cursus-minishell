/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:39 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/21 21:53:08 by asouinia         ###   ########.fr       */
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

/**
 * @brief check if all opened quotes and double quotes are closed
 * 
 * @param line the line read from prompt
 * @return int 0 if at least one quote still open and 1 if all quotes are closed
 */
int	check_quotes(char *line)
{
	int	i;
	int	signleq[2];
	int	doubleq[2];

	i = 0;	
	signleq[0] = 0;
	signleq[1] = 1;
	doubleq[0] = 0;
	doubleq[1] = 1;
	while (line && line[i])
	{
		if (line[i] != '\'' && line[i] != '"')
		{
			signleq[1] = signleq[1] * -1;
			doubleq[1] = doubleq[1] * -1;
		}
		if (line[i] == '\'')
			signleq[0] += signleq[1];
		if (line[i] == '"')
			doubleq[0] += doubleq[1];
		++i;
	}
	if (doubleq[0] || signleq[0])
		return (0);
	return (1);
}

void	readinputs(char **read)
{
	char	*str;
	//char	**cmds;
	//int		i;
	str = *read;
	while (1)
	{
		str = readline("minishell$ : ");
		printf("=> %s\n", str);
		
		printf("pipe checker %d\n", check_end_start_pipes(str));
		printf("quote checker %d\n", check_quotes(str));
		//printf("here_doc checker %d\n", checkheredoc(str));
		//cmds = split_cmds(str);
		free(str);
		//i = 0;
		//while (cmds && cmds[++i])
		//{
		//	printf("\t%s\n", cmds[i]);			
		//}
	}
}

int count_pipes(char *line)
{
	//int	i;
	int	signleq[2];
	int	doubleq[2];
	int	pipe[2];

	signleq[0] = 0;
	signleq[1] = 0;
	doubleq[0] = 0;
	doubleq[1] = 0;
	pipe[0] = 0;
	pipe[1] = 0;
	(void )line;
	return 0;
}


char **split_cmds(char *line)
{
	//int	*pipe_idxs;
	(void )line;
	return (NULL);
}