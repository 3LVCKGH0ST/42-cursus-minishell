/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:38:25 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 01:08:50 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

int	skipsinglequotes(char **tmp, char *str, int i)
{
	i++;
	while (str[i] && str[i])
	{
		if (str[i] == '\'')
			break ;
		chartostr(&(*tmp), str[i]);
		i++;
	}
	return (i);
}

void	varreplcae(char **tmp, char *cmd, char **env)
{
	char	*t;
	int		i;
	char	*c;

	i = -1;
	c = ft_strjoin(cmd, "=");
	while (env[++i])
	{
		if (ft_strncmp(env[i], c, ft_strlen(c)) == 0)
		{
			t = *tmp;
			*tmp = ft_strjoin(*tmp, env[i] + ft_strlen(cmd) + 1);
			free(c);
			free(t);
			return ;
		}
	}
	free(c);
}

int	handlvar(char **tmp, char *str, char **env, int i)
{
	char	*cmd;
	int		f;

	i++;
	f = i;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	cmd = ft_substr(str, f, i - f);
	varreplcae(&(*tmp), cmd, env);
	i--;
	free(cmd);
	return (i);
}

static void	expand_inter(char *tmp1[2], char *tmp, int *i)
{
	tmp1[0] = tmp;
	tmp1[1] = ft_itoa(g_global.prev_exit_code);
	tmp = ft_strjoin(tmp, tmp1[1]);
	free(tmp1[0]);
	free(tmp1[1]);
	(*i)++;
}

char	*builder_expand_id(char *str, char **env)
{
	char	*tmp;
	char	*tmp1[2];
	int		i;

	i = -1;
	tmp = malloc(1);
	tmp[0] = 0;
	while (str[++i])
	{
		if ((str[i] == '"' && str[0] != '\'') || \
		(str[i] == '\'' && str[0] == '\''))
			continue ;
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			expand_inter(tmp1, tmp, &i);
			continue ;
		}
		else if (str[i] == '$' && str[i + 1] == '$' && str[0] != '\'')
			chartostr(&tmp, str[i]);
		else if (str[i] == '$' && str[0] != '\'')
			i = handlvar(&tmp, str, env, i);
		else
			chartostr(&tmp, str[i]);
	}
	return (tmp);
}
