/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:59 by mbalagui          #+#    #+#             */
/*   Updated: 2022/04/21 05:25:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "../parsing/inc/parser_bonus.h"
# include "../parsing/inc/lexer_bonus.h"
# include "../parsing/inc/print_tree_bonus.h"
# include "../builder/inc/builder_bonus.h"
# include "../execute/inc/execute_bonus.h"
# include "../signals/inc/signals_bonus.h"

void	showenv(char **envp, int fd);
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
void	before_exec(char *str, char **envp);
void	free_all(t_lexer *lexer, t_parser *parser, \
t_ast *ast, t_d_list *builder);
void	init_minishell(void);
void	free_heredoc(void *c);
int		loop_heredoc(void);

#endif