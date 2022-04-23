/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:39:18 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 21:37:12 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parser_bonus.h"

void	free_2d_short(short ***arr, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free((*arr)[i]);
	free(*arr);
}

short	**init_2d(int len1, int len2)
{
	int		i;
	short	**arr;

	i = -1;
	arr = (short **)malloc(sizeof(short *) * len1);
	if (!arr)
		return (NULL);
	while (++i < len1)
	{
		arr[i] = (short *)malloc(sizeof(short) * len2);
		ft_bzero(arr[i], sizeof(short) * len2);
	}
	return (arr);
}
