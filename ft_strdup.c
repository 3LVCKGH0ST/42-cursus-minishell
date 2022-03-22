/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:57:19 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/22 18:59:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *) malloc(len + 1);
	if (s2)
		return ((char *)ft_memcpy(s2, s1, len + 1));
	return (NULL);
}

/**
 * @brief duplicate from start to end
 * 
 * @param s1 string to duplicate from
 * @param idx_start index of start
 * @param idx_end index of end
 * @return char* duplicated string
 */
char	*ft_strdup_v2(char *s1, int idx_start, int idx_end)
{
	size_t	len;
	char	*s2;

	len = idx_end - idx_start + 1;
	s2 = malloc(len + 1);
	if (!s2 || !s1)
		return (NULL);
	s2[len] = '\0';
	return ((char *)ft_memcpy(s2, s1 + idx_start, len));
}
