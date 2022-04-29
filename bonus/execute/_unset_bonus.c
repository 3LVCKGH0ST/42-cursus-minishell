/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:58:57 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/29 01:06:36 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute_bonus.h"

int	checkspchar(char *k, char	*v, int c)
{
	int	i;

	i = -1;
	while (k[++i])
	{
		if ((!ft_isalnum(k[i]) && k[i] != '_') || ft_isdigit(k[0]))
		{
			if (!c)
			{
				ft_putstr_fd("unset: `", 2);
				ft_putstr_fd(k, 2);
				ft_putstr_fd("' : not a valid identifier\n", 2);
			}
			else
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(k, 2);
				ft_putchar_fd('=', 2);
				ft_putstr_fd(v, 2);
				ft_putstr_fd("' : not a valid identifier\n", 2);
			}
			return (1);
		}
	}
	return (0);
}

void	unset_env(char ***env, char	*key)
{
	char	**tmp;
	char	*chck;
	int		i;
	int		j;

	if (checkspchar(key, NULL, 0))
		return ;
	tmp = *(env);
	i = -1;
	j = 0;
	chck = ft_strjoin(key, "=");
	(*env) = malloc(sizeof(char *) * getlenenv(tmp) + sizeof(char *));
	while (tmp[++i])
	{
		if (ft_strncmp(tmp[i], chck, ft_strlen(chck)) != 0)
			(*env)[i - j] = tmp[i];
		else
		{
			free(tmp[i]);
			j = 1;
		}
	}
	(*env)[i - j] = NULL;
	free(tmp);
	free(chck);
}
