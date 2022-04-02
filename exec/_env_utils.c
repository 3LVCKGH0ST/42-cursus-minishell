/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:11 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 21:10:40 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

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
	char		*tmp1;

	i = -1;
	chck = ft_strjoin(key, "=");
	while ((*env)[++i])
	{
		if (startwith((*env)[i], chck))
		{
			free((*env)[i]);
			tmp1 = ft_strdup((char *)expv);
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
