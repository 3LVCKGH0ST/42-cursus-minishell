/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 03:28:09 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 04:51:43 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/execute.h"

void	ft_exit(char	**args)
{
	int			is_int;
	long long	exit_code;

	is_int = 1;
	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	exit_code = ft_atoi_v2(args[1], &is_int);
	if (is_int == 0)
	{
		write(1, "minishell: exit: ", 18);
		write(1, args[1], ft_strlen(args[1]));
		write(1, ": numeric argument required\n", 29);
		exit(255);
	}
	if (args[2])
	{
		write(1, "minishell: exit: too many arguments\n", 37);
		g_global.exit_code = 1;
		return ;
	}
	exit(exit_code % 256);
}

static long long	check_ft_atoi_inter(int sign, unsigned long long \
nbr, char c, int *is)
{
	nbr = nbr * 10 + c - '0';
	if (nbr > 9223372036854775808ULL)
	{
		*is = 0;
		return (0);
	}
	if (nbr == 9223372036854775808ULL && sign > 0)
	{
		*is = 0;
		return (0);
	}
	return (nbr);
}

long long	ft_atoi_v2(const char *str, int *is_int)
{
	int					i;
	unsigned long long	nbr;
	int					sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] == ' '))
		++i;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[++i] < '0' || str[i] > '9')
			return (*is_int = 0, 0);
	}
	else if (str[i] < '0' || str[i] > '9')
		return (*is_int = 0, 0);
	while (str[i] >= '0' && str[i] <= '9')
		nbr = check_ft_atoi_inter(sign, nbr, str[i++], is_int);
	if ((str[i] == ' ') || (str[i] == '\0'))
		return (sign * nbr);
	return (*is_int = 0, 0);
}
