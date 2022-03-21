/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:39 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/21 18:33:32 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkpipes(char	*str)
{
	int	i;

	i = skiprtspace(str);
	if (str[i] == '|')
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
	if (str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		i = skiplfspace(str, i);
		while (str[i])
		{
			if (str[i] == '<' || str[i] == '>')
				return (-1);
			printf("%c", str[i]);
			i++;
		}
		returnval = 1;
	}
	return (returnval);
}

void	readinputs(char **read)
{
	char	*str;

	str = *read;
	while (1)
	{
		str = readline("minishell : ");
		printf("=> %s\n", str);
		printf("pipe checker %d\n", checkpipes(str));
		printf("here_doc checker %d\n", checkheredoc(str));
		free(str);
	}
}
