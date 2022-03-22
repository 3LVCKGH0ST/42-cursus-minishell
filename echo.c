/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:04:13 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 13:14:10 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief wirte a string in the console
 * 
 * @param str string
 * @param newline = 1 ? with new ligne : without
 */

void	ft_echo(char *str, int newline)
{
	if (str)
	{
		printf("%s", str);
		if (newline)
			printf("\n");
	}
}
