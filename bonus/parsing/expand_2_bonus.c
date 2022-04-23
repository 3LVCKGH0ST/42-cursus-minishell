/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 00:47:44 by asouinia         ###   ########.fr       */
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
	lst = ft_d_lstnew(tmp);
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
