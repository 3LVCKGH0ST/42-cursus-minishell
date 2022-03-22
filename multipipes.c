/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:28:34 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 13:55:17 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	emptypipes(char *str)
{
	int	i;
	int	c;
	int d;

	i = skiplfspace(str, 0);
	c = 0;
	d = 0;
	if (str[i] != '|')
		return (-1);
	while (str[i])
	{
		if (str[i] != '|')
		{
			if (c > d)
				d = c;
			c = 0;
		}
		if (str[i] == '|')
			c++;
		i++;
	}
	if (c > d)
		d = c;
	if (d == 1)
		return (0);
	return (d);
}
