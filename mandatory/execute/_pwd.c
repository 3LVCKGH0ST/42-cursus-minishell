/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:27 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:20:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

/**
 * @brief Get the path object
 * 
 * @param envp 
 * @return char* 
 */
char	*get_path(char **envp)
{
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PWD", 4))
		i++;
	return (envp[i] + 4);
}
