/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:00:20 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/21 22:50:18 by mbalagui         ###   ########.fr       */
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

int	quotescheckers(char *str)
{
	int	singleq;
	int	doubleq;
	int	i;

	i = 0;
	singleq = 0;
	doubleq = 0;
	while (str[++i])
	{
		if (str[i] == '"' && singleq == 0)
		{
			doubleq = !doubleq;
		}
		if (str[i] == '\'' && doubleq == 0)
		{
			singleq = !singleq;
		}
	}
	printf("=> double : %d\n", doubleq);
	printf("=> sinmg : %d\n", singleq);
	return (0);
}
