/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 02:42:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

t_d_list	*expand_word(char *str)
{
	t_d_list	*tmp;

	tmp = expand_layer1(get_expanded_word(str));
	return (tmp);
}

t_d_list	*expand_layer1(char *str)
{
	t_d_list	*lst;
	int			i;

	lst = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			ft_d_lstadd_back(&lst, ft_d_lstnew(collect_str(&i, str)));
	}
	free(str);
	return (lst);
}

char	*get_expanded_word(char *str)
{
	char	*line;
	int		i;

	i = -1;
	line = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			line = ft_skip_quotes(str, line, &i);
		else if (str[i] == '$' && (str[i + 1] == '$' || str[i + 1] == '?' \
		|| ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			line = ft_skip_var(str, line, &i);
		else
			line = append_char(line, str[i]);
	}
	return (line);
}

char	*collect_str(int *i, char *str)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\'' || str[*i] == '"')
			tmp = collect_str_quoted(i, str, tmp);
		else
			tmp = append_char(tmp, str[*i]);
		(*i)++;
	}
	(*i)--;
	return (tmp);
}

char	*collect_str_quoted(int *i, char *str, char *prev)
{
	char	*tmp;
	char	quote;

	quote = str[(*i)++];
	tmp = prev;
	while (str[*i] && str[*i] != quote)
		tmp = append_char(tmp, str[(*i)++]);
	return (tmp);
}
