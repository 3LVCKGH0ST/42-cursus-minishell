/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:44 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/09 02:18:42 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# include "../../../libft/libft.h"
# include "../../../double_linked_list/double_linked_list.h"
# include "../../inc/structs.h"
# include "../../parsing/inc/parser.h"

typedef enum e_builder_type {
	B_CMD,
	B_AND,
	B_OR,
}	t_builder_type;
typedef struct s_builder
{
	t_builder_type	type;
	t_cmd			*cmd;
	t_d_list		*left;
	t_d_list		*right;
	int				pipefd[2];
	int				status;
}				t_builder;

t_builder	*builder_init_builder(t_builder_type type);
t_d_list	*builder_build(t_ast *ast, char **env);
t_d_list	*builder_build_pipline(t_ast *ast, char **env);
t_d_list	*builder_build_op(t_ast *ast, char **env);
t_builder	*builder_build_list(t_ast *ast, char **env);
t_redir		*builder_build_redir(t_ast *ast, char **env);
char		*builder_build_id(t_ast *ast, char **env);
void		ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode);
char		*builder_expand_id(char	*str, char **env);
void		print_builder_pipline(t_d_list *build);
void		print_builder_op(t_builder *build);
void		print_builder(t_d_list *build);
void		builder_free_builder_redir(t_d_list *redir);
void		builder_free_builder_pipline(t_d_list *build);
void		builder_free_builder_op(t_builder *build);
void		builder_free_builder(t_d_list *build);

char		**g_env;
#endif