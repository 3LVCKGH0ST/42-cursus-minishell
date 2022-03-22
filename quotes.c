/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:00:20 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 09:06:59 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	initchecker(int *t1, int *t2, int *index)
// {
// 	t1[0] = 0;
// 	t1[1] = 0;
// 	t2[0] = 0;
// 	t2[1] = 0;
// 	*index = 0;
// }
/**
 * @brief check if all opened quotes and double quotes are closed
 * 
 * @param str the line read from prompt
 * @param end check until index end - 1
 * @return int 0 if at least one quote still open and 1 if all quotes are closed
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
	return (!(doubleq || singleq));
}
