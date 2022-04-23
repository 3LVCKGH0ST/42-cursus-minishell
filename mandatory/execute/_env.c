/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	showenv(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], fd);
		ft_putchar_fd('\n', fd);
	}
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

	if (!val)
		return (NULL);
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
	char	*kval;
	int		i;

	if (handldup(&(*env), key, val))
		return ;
	tmp = *(env);
	i = -1;
	(*env) = malloc(sizeof(char *) * getlenenv(tmp) + sizeof(char *) * 2);
	while (tmp[++i])
		(*env)[i] = tmp[i];
	if (val)
	{
		kval = exportval(key, val);
		(*env)[i++] = kval;
	}
	else
	{
		kval = ft_strdup(key);
		(*env)[i++] = kval;
	}
	(*env)[i] = NULL;
	free(tmp);
}
