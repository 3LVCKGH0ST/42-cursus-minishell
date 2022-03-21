/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:15:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/21 18:33:10 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"


char **split_pipes()
{
	
}

int main(int argc, char  **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	char *str;
	str = readline("minishell$ ");
	printf(" |%s|\n", str);
	return (0);
}

