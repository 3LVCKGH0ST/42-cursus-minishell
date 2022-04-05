/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:39:02 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/31 15:24:25 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/token.h"

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

void	free_token(void *token)
{
	t_token	*tmp;

	if (token)
	{
		tmp = (t_token *)token;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
