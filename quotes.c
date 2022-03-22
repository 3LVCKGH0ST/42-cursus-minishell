/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:00:20 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 13:27:08 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if all opened quotes and double quotes are closed
 * 
 * @param str the line read from prompt
 * @param end check until index end - 1
 * @return int 1 if signle quote is open 2 if double quote is open 0 if all qotes are closed
 */
int	quotescheckers(char *str, int end)
{
	int	singleq;
	int	doubleq;
	int	i;

	i = 0;
	singleq = 0;
	doubleq = 0;
	while (str && str[i] && i < end)
	{
		if (str[i] == '"' && singleq == 0)
			doubleq = !doubleq;
		if (str[i] == '\'' && doubleq == 0)
			singleq = !singleq;
		++i;
	}
	return (singleq + doubleq * 2);
}
