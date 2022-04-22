/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 02:05:50 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 04:02:19 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

char	**parse_paths(void)
{
	int		i[2];
	int		k;
	char	**paths;
	char	*str;

	i[0] = -1;
	i[1] = count_paths();
	paths = malloc(sizeof(char *) * (i[1] + 2));
	paths[i[1] + 1] = NULL;
	k = -1;
	str = ft_strchr(get_env_var(g_global.env, "PATH"), '=') + 1;
	while (i[0] < i[1])
		paths[++(i[0])] = fill_paths(str, &k);
	return (paths);
}

int	count_paths(void)
{
	int		i;
	int		count;
	char 	*str;

	i = -1;
	count = 0;
	str = get_env_var(g_global.env, "PATH");
	while (str[++i])
	{
		if (str[i] == ':')
			count++;
	}
	return (count);
}

char	*fill_paths(char *path, int *k)
{
	int		i;
	char	*tmps[2];
	char	*str;

	i = -1;
	str = ft_strdup("");
	*k = *k + 1;
	while (path[*k] && path[*k] != ':')
	{
		tmps[1] = to_str(path[*k]);
		tmps[0] = ft_strjoin(str, tmps[1]);
		free(str);
		free(tmps[1]);
		str = tmps[0];
		*k = *k + 1;
	}
	if (!str[0])
		return (str);
	tmps[0] = str;
	str = ft_strjoin(str, "/");
	return (free(tmps[0]), str);
}