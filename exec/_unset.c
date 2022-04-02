/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:58:57 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 18:52:42 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(char ***env, char	*key)
{
	char	**tmp;
	char	*chck;
	int		i;
	int		j;

	(void)key;
	tmp = *(env);
	i = -1;
	j = 0;
	chck = ft_strjoin(key, "=");
	(*env) = malloc(sizeof(char *) * getlenenv(tmp) + sizeof(char *));
	while (tmp[++i])
	{
		if (ft_strncmp(tmp[i], chck, ft_strlen(chck)) != 0)
			(*env)[i - j] = tmp[i];
		else
		{
			free(tmp[i]);
			j = 1;
		}
	}
	(*env)[i - j] = NULL;
	free(tmp);
	free(chck);
}
