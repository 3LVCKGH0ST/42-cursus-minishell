/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:34:10 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/21 18:17:09 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	skiplfspace(char *str, int index)
{
	while (str[index] == ' ')
		index++;
	return (index);
}

int	skiprtspace(char *str)
{
	int	index;

	index = ft_strlen(str) - 1;
	while (str[index] == ' ')
		index--;
	return (index);
}
