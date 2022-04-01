/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:11 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/01 18:46:45 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	startwith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}

int	handldup(char ***env, char *key, char *val)
{
	char		*chck;
	const char	*expv = exportval(key, val);
	int			i;

	i = -1;
	chck = ft_strjoin(key, "=");
	while ((*env)[++i])
	{
		if (startwith((*env)[i], chck))
		{
			free(chck);
			(*env)[i] = 0;
			(*env)[i] = (char *)expv;
			return (1);
		}
	}
	free(chck);
	return (0);
}
