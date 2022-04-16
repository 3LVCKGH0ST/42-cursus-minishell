/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/16 21:22:12 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	showenv(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

int	getlenenv(char	**env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	createclone(char ***to, char **from)
{
	int	i;

	i = -1;
	(*to) = malloc(sizeof(char *) * getlenenv(from) * 2);
	while (from[++i])
	{
		(*to)[i] = ft_strdup(from[i]);
	}
	(*to)[i] = NULL;
}

char	*exportval(char *key, char *val)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(ft_strlen(key) + ft_strlen(val) + 2);
	while (key[++i])
		ret[i] = key[i];
	ret[i] = '=';
	while (val[++i - ft_strlen(key) - 1])
		ret[i] = val[i - ft_strlen(key) - 1];
	ret[i] = 0;
	return (ret);
}

void	addenv(char ***env, char *key, char *val)
{
	char	**tmp;
	int		i;

	if (checkspchar(key, val))
		return ;
	if (handldup(&(*env), key, val))
		return ;
	tmp = *(env);
	i = -1;
	(*env) = malloc(sizeof(char *) * getlenenv(tmp) + sizeof(char *) * 2);
	while (tmp[++i])
		(*env)[i] = tmp[i];
	(*env)[i++] = exportval(key, val);
	(*env)[i] = NULL;
	free(tmp);
}
