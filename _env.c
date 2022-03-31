/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:10:09 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/31 21:48:25 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**addenv(char **env, char *key, char *val)
{
	char	**tmp;
	char	*exp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(char *) * getlenenv(env) + sizeof(char *) * 2);
	while (env[++i])
		tmp[i] = env[i];
	exp = exportval(key, val);
	tmp[i] = exp;
	tmp[i + 1] = NULL;
	free(exp);
	return (tmp);
}
