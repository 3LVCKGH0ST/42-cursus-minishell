/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:58:57 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/20 01:33:41 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

int	checkspchar(char *k, char	*v)
{
	int	i;

	i = -1;
	while (k[++i])
	{
		if (!ft_isalnum(k[i]) && k[i] != '_' && ft_isdigit(k[0]))
		{
			(!v) && printf("unset: `%s' : not a valid identifier\n", k);
			(v) && printf("export: `%s=%s': not a valid identifier\n", k, v);
			return (1);
		}
	}
	return (0);
}

void	unset_env(char ***env, char	*key)
{
	char	**tmp;
	char	*chck;
	int		i;
	int		j;

	if (checkspchar(key, NULL))
		return ;
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
