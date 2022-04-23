/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 06:14:38 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

t_d_list	*expand_word(char *str)
{
	t_d_list	*lst;
	int			i;
	char		*pattern;
	int			*stars_idxs;

	lst = NULL;
	i = -1;
	str = get_expanded_word(str);
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			pattern = collect_str(&i, str, &stars_idxs);
			if (stars_idxs[0] == -1)
				ft_d_lstadd_back(&lst, ft_d_lstnew(pattern));
			else
				ft_d_lstadd_back_v2(&lst, get_matches(pattern, stars_idxs));
			free(stars_idxs);
		}
	}
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

int	count_stars(char *str)
{
	int		i;
	int		stars;
	char	quote;
	int		inquote;

	i = -1;
	inquote = 0;
	stars = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (inquote == 0)
			{
				quote = str[i];
				inquote = 1;
			}
			else if (str[i] == quote)
				inquote = 0;
		}
		else if (str[i] == '*' && !inquote)
			stars++;
	}
	return (stars);
}

char	*collect_str(int *i, char *str, int **stars_idxs)
{
	char	*tmp;
	int		j;
	int		stars;

	tmp = ft_strdup("");
	stars = count_stars(str);
	j = -1;
	*stars_idxs = malloc(sizeof(int) * (stars + 1));
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\'' || str[*i] == '"')
			tmp = collect_str_quoted(i, str, tmp);
		else if (str[*i] == '*')
		{
			tmp = append_char(tmp, str[*i]);
			(*stars_idxs)[++j] = ft_strlen(tmp) - 1;
		}
		else
			tmp = append_char(tmp, str[*i]);
		(*i)++;
	}
	(*i)--;
	(*stars_idxs)[++j] = -1;
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
