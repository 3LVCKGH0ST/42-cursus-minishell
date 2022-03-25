/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:01:53 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/24 22:46:41 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_char(char *line, char end)
{
	int i;

	i = 0;
	while (line && line[i] && line[i] != end)
			i++;
	return(i);
}

int	parse_pipe(char *line)
{
	int i;

	i = 0;
	while (line && line[i] && line[i] != '|')
	{
		if (line[i] == '"')
			i += parse_char(line + i + 1, '"');
		else if (line[i] == '\'')
			i += parse_char(line + i + 1, '\'');
		i++;
		//printf("{%s}", line +i);
	}
	return(i);
}

int	parse (char *line)
{
	int i;

	i = 0;
	while (line && line[i] && line[i] != ' ')
	{
		if (line[i] == '"')
			i += parse_char(line + i + 1, '"');
		else if (line[i] == '\'')
			i += parse_char(line + i + 1, '\'');
		i++;
		if (line[i] == '"' || line[i] == '\'')
			i++;
	}
	return(i);
}

void	readinputs(char **read)
{
	char	*str;
	//char	**cmds;
	//char	**sss;
	int		i;
	int		j;
	int		ii;
	int		jj;
	int		k;
	int		l;
	char	*tmp;

	str = *read;
	while (1)
	{
		str = readline("minishell$ : ");
		//printf("==>==>==>==>\t%s\n", ft_strdup_v2(str, 0, parse(str)));
		ii = 0;
		while (ii < (int)ft_strlen(str))
		{
			j = parse_char(str + ii, ')');
			tmp = ft_strdup_v2(str, i, i + j - 1);
			printf("==>\t%s\n", tmp);
			k = 0;
			while (k < (int)ft_strlen(tmp))
			{
				l = parse(tmp + k);
				printf("\t\t\t%s\n", ft_strdup_v2(tmp, k, k + l - 1));
				k += l + 1;
			}
			ii += jj + 1;
		}

		i = 0;
		while (i < (int)ft_strlen(str))
		{
			j = parse_pipe(str + i);
			tmp = ft_strdup_v2(str, i, i + j - 1);
			printf("==>\t%s\n", tmp);
			k = 0;
			while (k < (int)ft_strlen(tmp))
			{
				l = parse(tmp + k);
				printf("\t\t\t%s\n", ft_strdup_v2(tmp, k, k + l - 1));
				k += l + 1;
			}
			i += j + 1;
		}

		//printf("pipe checker %d\n", check_end_start_pipes(str));
		//printf("quote checker %d\n", quotescheckers(str, ft_strlen(str)));
		//printf("multipipes : %d\n", count_max_multiple_pipes(str));
		//cmds = NULL;
		//if (count_max_multiple_pipes(str) <= 1 && check_end_start_pipes(str))
		//	cmds = split_cmds(str);
		free(str);
		//i = -1;
		//while (cmds && cmds[++i])
		//{
		//	printf("=>\t%s\n", cmds[i]);
		//	j = -1;
		//	sss = split_line(cmds[i]);
		//	while (sss && sss[++j])
		//	{
		//		printf("========>\t%s\n", sss[j]);
		//	}
		//}
	}
}
