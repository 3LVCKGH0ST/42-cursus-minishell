/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:55:39 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 05:53:56 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

int	check_outside_quotes(char *str)
{
	int		i;
	int		inside_quotes;
	char	quote;

	i = 0;
	inside_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			inside_quotes = !inside_quotes;
			quote = str[i];
		}
		if (str[i] == '$' && !inside_quotes)
			return (1);
		i++;
	}
	return (0);
}
