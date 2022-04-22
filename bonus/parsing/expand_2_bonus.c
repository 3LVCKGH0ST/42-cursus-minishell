/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 22:58:35 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

t_d_list	*expand_word(char *str)
{
	t_d_list	*tmp;

	tmp = expand_layer1(str);
	return (tmp);
}

t_d_list	*expand_layer1(char *str)
{
	t_d_list	*lst;
	int			i;
	char		*tmp;

	lst = NULL;
	i = -1;
	tmp = get_expanded_word(str);
	lst = ft_d_lstnew(parser_expand_id(str, g_global.env));
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
		else if (str[i] == '$')
			line = ft_skip_var(str, line, &i);
		else
			line = append_char(line, str[i]);
	}
	return (line);
}

char	*ft_skip_quotes(char *str, char *prev, int *i)
{
	char	quote;

	quote = str[(*i)++];
	prev = append_char(prev, quote);
	while (str[*i] && str[*i] != quote)
	{
		prev = append_char(prev, str[*i]);
		(*i)++;
	}
	prev = append_char(prev, quote);
	(*i)++;
	return (prev);
}

char	*ft_skip_var(char *str, char *prev, int *i)
{
	(void)i;
	(void)prev;
	return (str);
}

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
