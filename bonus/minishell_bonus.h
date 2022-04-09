/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:59 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/02 18:36:39 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

void	readinputs(char **read);
size_t	ft_strlen(const char *c);
int		skiplfspace(char *str, int defaultval);
int		skiprtspace(char *str);
char	**split_cmds(char *line);
int		quotescheckers(char *str, int end);
int		*get_pipe_idxs(char *line);
char	*ft_strdup_v2(char *s1, int idx_start, int idx_end);
int		emptypipes(char *str);
void	ft_echo(char *str);
int		count_max_multiple_pipes(char *str);
int		check_end_start_pipes(char *line);

char	**split_line(char *li);
void	showenv(char **envp);
void	addenv(char ***env, char *key, char *val);
char	*get_path(char **envp);
void	createclone(char ***to, char **from);
char	*exportval(char *key, char *val);
int		handldup(char ***env, char *key, char *val);
int		getlenenv(char	**env);
char	*expand_id(char	*str, char **env);
void	chartostr(char **str, char c);
void	change_dir(char ***env, char *to);
void	unset_env(char ***env, char	*key);
#endif