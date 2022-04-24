/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 04:58:29 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/24 00:19:47 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

static char	*get_dir_name(char	*dirname, char *pattern)
{
	char	*tmp;
	int		i;

	i = 0;
	if (pattern[0] != '.' || pattern[1] != '/')
		return (ft_strdup(dirname));
	tmp = NULL;
	tmp = append_char(tmp, '.');
	while (pattern[++i] == '/')
		tmp = append_char(tmp, '/');
	tmp = append_str(tmp, ft_strdup(dirname));
	return (tmp);
}

t_d_list	*get_matches(char *pattern, int *stars_idxs)
{
	t_d_list		*tmp;
	DIR				*currdir;
	struct dirent	*dir;
	char			*tmp1;

	tmp = NULL;
	currdir = opendir(".");
	if (!currdir)
		return (ft_d_lstnew(pattern));
	dir = readdir(currdir);
	while (dir)
	{
		if (dir->d_name[0] != '.')
		{
			tmp1 = get_dir_name(dir->d_name, pattern);
			if (is_match_pattern(tmp1, pattern, ft_strlen(pattern), stars_idxs))
				ft_d_lstadd_back(&tmp, ft_d_lstnew(ft_strdup(tmp1)));
			free(tmp1);
		}
		dir = readdir(currdir);
	}
	if (!tmp)
		tmp = ft_d_lstnew(ft_strdup(pattern));
	closedir(currdir);
	return (tmp);
}

int	is_valid_star(int idx, int *stars_idxs)
{
	int	i;

	i = -1;
	while (stars_idxs[++i] >= 0)
	{
		if (stars_idxs[i] == idx)
			return (1);
	}
	return (0);
}

int	is_match_pattern(char *str, char *pattern, int s_p, int *stars)
{
	int		i;
	int		j;
	int		s_f;
	short	**lookup;

	s_f = ft_strlen(str);
	if (s_p == 0)
		return (s_f == 0);
	lookup = set_lookup(pattern, stars, str, s_p);
	i = 0;
	while (++i <= s_f)
	{
		j = 0;
		while (++j <= s_p)
		{
			if (pattern[j - 1] == '*' && is_valid_star(j - 1, stars))
				lookup[i][j] = (lookup[i][j - 1] || lookup[i - 1][j]);
			else if (str[i - 1] == pattern[j - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			else
				lookup[i][j] = 0;
		}
	}
	i = lookup[s_f][s_p];
	return (free_2d_short(&lookup, s_f + 1), i);
}

short	**set_lookup(char *pattern, int *stars, char *str, int s_p)
{
	int		j;
	short	**lookup;

	j = 0;
	lookup = init_2d(ft_strlen(str) + 1, s_p + 1);
	if (!lookup)
		return (NULL);
	lookup[0][0] = 1;
	while (++j <= s_p)
		if (pattern[j - 1] == '*' && is_valid_star(j - 1, stars))
			lookup[0][j] = lookup[0][j - 1];
	return (lookup);
}
