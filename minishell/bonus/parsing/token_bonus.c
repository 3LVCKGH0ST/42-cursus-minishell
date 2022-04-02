/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:39:02 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 17:56:36 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_bonus.h"

t_token	*init_token(char *value, t_e_token type)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->type = type;
	tmp->value = value;
	return (tmp);
}
