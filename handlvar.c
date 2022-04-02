/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:38:25 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 01:38:02 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chartostr(char **str, char c)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = -1;
	tmp = *str;
	tmp1 = malloc(2);
	tmp1[0] = c;
	tmp1[1] = '\0';
	*str = ft_strjoin(tmp, tmp1);
	free(tmp1);
	free(tmp);
}

int	skipsinglequotes(char **tmp, char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == '\'')
			break ;
		chartostr(&(*tmp), str[i]);
	}
	return (i);
}

void	varreplcae(char	**tmp, char *cmd, char **env)
{
	char	*t;
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], cmd, ft_strlen(cmd)) == 0)
		{
			t = *tmp;
			*tmp = ft_strjoin(*tmp, env[i] + ft_strlen(cmd) + 1);
			free(t);
			return ;
		}
	}
}

int	handlvar(char **tmp, char *str, char **env, int i)
{
	const char	*spchar = "'\"$ ";
	char		*cmd;
	int			f;

	i++;
	f = i;
	while (!ft_strchr(spchar, str[i]))
		i++;
	cmd = ft_substr(str, f, i - f);
	varreplcae(&(*tmp), cmd, env);
	i--;
	free(cmd);
	return (i);
}

char	*expand_id(char	*str, char **env)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = malloc(1);
	tmp[0] = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			i = skipsinglequotes(&tmp, str, i);
		else if (str[i] == '"')
			continue ;
		else if (str[i] == '$')
			i = handlvar(&tmp, str, env, i);
		else
			chartostr(&tmp, str[i]);
	}
	printf("\n---? %s\n", tmp);
	return (tmp);
}
