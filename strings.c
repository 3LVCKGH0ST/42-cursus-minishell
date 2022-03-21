/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:34:10 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/21 20:30:46 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

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
