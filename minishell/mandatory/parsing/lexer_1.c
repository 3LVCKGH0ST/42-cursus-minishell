/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:34:05 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 09:33:04 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lexer.h"	

/**
 * @brief return a string of the current char
 * 
 * @param c 
 * @return char* c\0
 */
char	*to_str(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/**
 * @brief check if the character is not a reserved token 
 * 
 * @param c 
 * @return int *1* if reserved *0* if not
 */
int	is_reserved_token(char c)
{
	if (ft_strchr("&|()<> \t", c))
		return (1);
	return (0);
}
