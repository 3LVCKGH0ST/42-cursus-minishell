/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:48:19 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/06 02:03:47 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# define EXIT_SYNTAX_ERROR 258

typedef	struct s_global
{
	int	exit_code;
	
}			t_global;

t_global	g_global;

#endif