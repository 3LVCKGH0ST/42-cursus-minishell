/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 10:12:47 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

t_d_list	*expand_word(char *str)
{
	t_d_list	*tmp;

	tmp = ft_d_lstnew(str);
}

t_d_list	*expand_layer1(char *str)
{
	t_d_list	*lst;
	int			i;
	char		*tmp;
	char		*tmp1;

	lst = NULL;
	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		tmp = append_char(tmp, str[i]);
		if ((str[i] == '"' || str[i] == '\''))
		{
			tmp = ft_skip_quotes(tmp, i);
			continue ;
		}
	}
	return (lst);
}

char	*ft_skip_quotes(char *str, int *i)
{
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
