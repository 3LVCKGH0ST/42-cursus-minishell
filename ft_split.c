/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:40:03 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 16:41:07 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getsize(char *str, int c)
{
	int	count;
	int	check;
	int	i;

	i = 0;
	count = 0;
	check = 1;
	while (str[i])
	{
		if (str[i] != c && check == 1)
		{
			count++;
			check = 0;
			i++;
			continue ;
		}
		if (str[i] == c)
			check = 1;
		i++;
	}
	return (count);
}

void	setup(int *i, int *j, int *k)
{
	*k = 0;
	*j = 0;
	*i = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	if (!s)
		return (NULL);
	setup(&i, &j, &k);
	res = (char **)malloc((getsize((char *)s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i++] == c)
		{
			j++;
			continue ;
		}
		while (s[i] != c && s[i])
			i++;
		res[k++] = ft_substr(s, j, i - j);
		j = i;
	}
	res[k] = NULL;
	return (res);
}
