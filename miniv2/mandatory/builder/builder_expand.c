/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:38:25 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/08 01:03:53 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

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

char	*builder_expand_id(char *str, char **env)
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
		else if (str[i] == '$' && str[i + 1] == '$')
			chartostr(&tmp, str[i]);
		else if (str[i] == '$')
			i = handlvar(&tmp, str, env, i);
		else
			chartostr(&tmp, str[i]);
	}
	return (tmp);
}
