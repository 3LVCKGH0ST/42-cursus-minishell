/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:37:36 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 21:10:54 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"

/**
 * @brief 
 * 
 * @param str 
 * @param i 
 * @return int 
 */
int	getfrom(char *str, int i)
{
	while (str[++i])
	{
		if (str[i] != '-')
			return (0);
		else if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] == 'n')
				i++;
			if (str[i] == ' ')
			{
				while (str[i] == ' ')
					i++;
				if (str[i] == '-' && str[i + 1] == 'n' && str[i - 1] == ' ')
					return (getfrom(str, i - 1));
				return (i);
			}
			else if (str[i - 1] == ' ')
				return (i - 2);
			else
				return (0);
		}
	}
	return (-1);
}
/**
 * @brief 
 * 
 * @param str 
 * @param i 
 * @return int 
 */

int	withnewline(char *str, int i)
{
	while (str[++i])
	{
		if (str[i] != '-')
			return (0);
		else if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] == 'n')
				i++;
			if (str[i] == ' ')
			{
				return (1);
			}
		}
	}
	return (0);
}

/**
 * @brief 
 * 
 * @param str 
 */
void	ft_echo(char *str)
{
	int	i;
	int	c;

	i = skiplfspace(str, 0);
	c = withnewline(str, i - 1);
	i = getfrom(str, i - 1);
	printf("%s", str + i);
	if (!c)
		printf("\n");
}

//int	main(void)
//{
//	ft_echo(" -n -n -n -n -n -n -nnnnnn daf");
//	return (0);
//}
