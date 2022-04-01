/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:33:26 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/01 18:30:07 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	(void)envp;
	createclone(&env, envp);
	addenv(&env, "OLDPWD", "test");
	addenv(&env, "OLDPWD", "te2st");
	addenv(&env, "OLDPWD", "test");
	addenv(&env, "OLDPWD", "tes33131t");
	addenv(&env, "OLDPWD", "hwlo fwfew");
	addenv(&env, "OLDPWD1d3", "2test");
	addenv(&env, "OLDPWD13", "2test");
	addenv(&env, "OLDPWD13", "2test");
	addenv(&env, "OLDPWD13", "2test");
	addenv(&env, "OLDPWD13", "2test");
	addenv(&env, "OLDPWD134", "2test");
	addenv(&env, "OLDPWD13", "2test");
	showenv(env);
	system("leaks minishell");
	//readinputs(&input);
	return (0);
}
