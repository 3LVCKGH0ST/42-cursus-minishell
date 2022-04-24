/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:27:31 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/22 09:07:46 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../../builder/inc/builder.h"
# include <readline/readline.h>
# include <errno.h>
# include <dirent.h>

# define COMMAND_NOT_FOUND_ERROR 127

void		iter_builder_pipline(t_d_list *build);
void		iter_builder_op(t_builder *build);
void		iter_builder(t_d_list *build);
void		execute(t_d_list *node);
int			open_in_files(t_d_list *node);
int			open_here_doc(t_d_list *node);
int			here_doc_run(t_redir *here_doc);
int			open_out_files(t_d_list *node);
void		close_cmd_fds(t_d_list *node);

char		*get_env_var(char **envp, char *env_var);
char		**get_paths(char **envp);
char		*get_cmd_full_path(char **envp, char *cmd);
int			exec_cmmand(t_cmd *cmd, char **env, int fd_pipe_in);

void		showenv(char **envp, int fd);
void		createclone(char ***to, char **from);
char		*exportval(char *key, char *val);
void		addenv(char ***env, char *key, char *val);
void		change_dir(char ***env, char *to);
void		ft_echo(char **str);
int			startwith(char *s1, char *s2);
int			handldup(char ***env, char *key, char *val);
char		*get_path(char **envp);
void		unset_env(char ***env, char	*key);
int			skiplfspace(char *str, int index);
int			skiprtspace(char *str);
int			checkspchar(char *k, char	*v);
int			getlenenv(char	**env);
void		showexport(int fd);
void		ft_export(char **args, int fd);
void		echo(char	**args);
void		setexport(char *key, char *val);
char		*lower(char *str);
int			execbuilt(t_cmd *cmd);
void		exec_file_sh(t_cmd *cmd);
char		**clone_args(char **args);
void		ft_exit(char	**args);
long long	ft_atoi_v2(const char *str, int *is_int);
int			count_paths(void);
char		*fill_paths(char *path, int *k);
char		**parse_paths(void);
void		print_error_fd(t_d_list	*node);

#endif