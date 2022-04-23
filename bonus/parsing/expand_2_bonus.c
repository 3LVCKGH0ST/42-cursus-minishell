/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 04:39:23 by asouinia         ###   ########.fr       */
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
	int			stars;
	int			*stars_idxs;

	lst = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			stars = 0;
			ft_d_lstadd_back(&lst, ft_d_lstnew(collect_str(&i, \
			str, &stars_idxs, &stars)));
			if (stars)
				free(stars_idxs);
		}
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

char	*collect_str(int *i, char *str, int **stars_idxs, int *stars)
{
	char	*tmp;
	int		j;

	tmp = ft_strdup("");
	*stars = count_stars(str);
	j = -1;
	if (*stars)
		*stars_idxs = malloc(sizeof(int) * (*stars));
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
