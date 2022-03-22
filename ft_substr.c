/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:40:50 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 16:41:18 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen((char *)s);
	if (len > l)
		res = malloc(l + 1);
	else
		res = malloc(len + 1);
	j = 0;
	i = start;
	if (!res)
		return (NULL);
	while (i < ft_strlen((char *)s) && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
