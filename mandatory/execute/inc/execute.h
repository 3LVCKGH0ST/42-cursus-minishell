/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:44:35 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/11 08:00:23 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTE_H
# define EXECUTE_H
# include "../../builder/inc/builder.h"
# include <readline/readline.h>
# include <errno.h>
#include <dirent.h>

# define COMMAND_NOT_FOUND_ERROR 127
void	iter_builder_pipline(t_d_list *build);
void	iter_builder_op(t_builder *build);
void	iter_builder(t_d_list *build);
void	execute(t_d_list *node);
int		open_in_files(t_d_list *node);
int		open_here_doc(t_d_list *node);
int		here_doc_run(t_redir *here_doc);
int		open_out_files(t_d_list *node);
void	close_cmd_fds(t_d_list *node);


char	*get_env_var(char **envp, char *env_var);
char	**get_paths(char **envp);
char	*get_cmd_full_path(char **envp, char *cmd);
int		exec_cmmand(t_cmd *cmd, char **env, int fd_pipe_in);
# endif