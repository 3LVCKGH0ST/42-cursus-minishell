/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:34:10 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/execute.h"

int	skiplfspace(char *str, int index)
{
	while (str && str[index] == ' ')
		index++;
	return (index);
}

int	skiprtspace(char *str)
{
	int	index;

	index = ft_strlen(str) - 1;
	if (index < 0)
		return (0);
	while (str && str[index] == ' ')
		index--;
	return (index);
}
