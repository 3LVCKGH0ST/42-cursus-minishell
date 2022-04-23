/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:38:25 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/23 03:59:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser.h"

char	*append_char(char	*str, char c)
{
	char	*tmp0;
	char	*tmp1;

	if (!str)
		str = ft_strdup("");
	tmp1 = to_str(c);
	tmp0 = ft_strjoin(str, tmp1);
	free(str);
	free(tmp1);
	return (tmp0);
}

char	*append_str(char	*str, char *c)
{
	char	*tmp0;

	if (!str)
		str = ft_strdup("");
	tmp0 = ft_strjoin(str, c);
	free(str);
	free(c);
	return (tmp0);
}

static	char	*get_var_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_strdup("");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		key = append_char(key, str[i]);
		i++;
	}
	return (key);
}

char	*ft_skip_var(char *str, char *prev, int *i)
{
	char	*value;
	char	*key;
	int		size;

	size = 1;
	if (str[(*i) + 1] == '?')
		value = ft_itoa(g_global.prev_exit_code);
	else if (str[(*i) + 1] == '$')
		value = ft_itoa(getpid());
	else
	{
		key = get_var_key(str + (*i) + 1);
		value = get_env_var(g_global.env, key);
		if (!value)
			value = ft_strdup("");
		else
			value = ft_strdup(ft_strchr(value, '=') + 1);
		size = ft_strlen(key);
		free(key);
	}
	prev = append_str(prev, value);
	(*i) += size;
	return (prev);
}

char	*ft_skip_quotes(char *str, char *prev, int *i)
{
	char	quote;

	quote = str[(*i)++];
	prev = append_char(prev, quote);
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && (str[(*i)] == '$' && (str[(*i) + 1] == '$' \
		|| str[(*i) + 1] == '?' || \
		ft_isalnum(str[(*i) + 1]) || str[(*i) + 1] == '_')))
			prev = ft_skip_var(str, prev, i);
		else
			prev = append_char(prev, str[*i]);
		(*i)++;
	}
	prev = append_char(prev, quote);
	return (prev);
}
