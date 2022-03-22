/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:53:06 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/22 17:53:25 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checkheredoc returns value : \n
 *	-1	:	parsing error
 *	 0	:	<< not found
 *	 1	:	0 errors
 * @param str 
 * @return int 
 */
int	checkheredoc(char *str)
{
	int	i;
	int	returnval;

	i = skiplfspace(str, 0);
	returnval = 0;
	if (str && str[i] == '<' && str[i + 1] == '<')
	{
		i += 2;
		i = skiplfspace(str, i);
		while (str && str[i])
		{
			if (str && (str[i] == '<' || str[i] == '>'))
				return (-1);
			printf("%c", str[i]);
			i++;
		}
		returnval = 1;
	}
	return (returnval);
}