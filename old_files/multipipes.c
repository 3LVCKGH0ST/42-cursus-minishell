/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:28:34 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 17:49:39 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  count max pipes in a row
 * 
 * @param str 
 * @return int 
 */
int	count_max_multiple_pipes(char *str)
{
	int	i;
	int	c;
	int	d;

	i = skiplfspace(str, 0);
	c = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] != '|')
		{
			if (c > d)
				d = c;
			c = 0;
		}
		if (str[i] == '|' && !quotescheckers(str, i))
			c++;
		i++;
	}
	if (c > d)
		d = c;
	return (d);
}
