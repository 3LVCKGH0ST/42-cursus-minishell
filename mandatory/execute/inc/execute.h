/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:44:35 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/09 03:36:11 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTE_H
# define EXECUTE_H
# include "../../builder/inc/builder.h"
# include <readline/readline.h>

void	iter_builder_pipline(t_d_list *build);
void	iter_builder_op(t_builder *build);
void	iter_builder(t_d_list *build);
void	execute(t_d_list *node);
int		open_in_files(t_d_list *node);
int		open_here_doc(t_d_list *node);
int		open_out_files(t_d_list *node);

# endif