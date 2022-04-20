/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:11 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/20 04:20:53 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

int	startwith(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i - 1] == '=' && s2[i - 1] == '=')
		return (1);
	if (s1[i] != s2[i] && s2[i] != '=' && s1[i] != '=')
		return (0);
	return (1);
}

static void	settmp(char **tmp, char *key, char *val, char *exp)
{
	if (val)
		(*tmp) = ft_strdup(exp);
	else
		(*tmp) = ft_strdup(key);
}

int	handldup(char ***env, char *key, char *val)
{
	char		*chck;
	const char	*expv = exportval(key, val);
	int			i;
	char		*tmp1;

	i = -1;
	if (val)
		chck = ft_strjoin(key, "=");
	else
		chck = ft_strdup(key);
	while ((*env)[++i])
	{
		if (startwith((*env)[i], chck))
		{
			free((*env)[i]);
			settmp(&tmp1, key, val, (char *) expv);
			(*env)[i] = tmp1;
			free((void *)expv);
			free(chck);
			return (1);
		}
	}
	free(chck);
	free((void *)expv);
	return (0);
}
