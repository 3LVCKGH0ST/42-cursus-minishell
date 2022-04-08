/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:28:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/08 01:55:45 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TREE_H
# define PRINT_TREE_H
# include "parser.h"
# include "../../../libft/libft.h"
# include "../../../double_linked_list/double_linked_list.h"

void	print_tree(t_ast *ast);
void	print_tree_id(t_ast *ast);
void	print_tree_redir(t_ast *ast);
void	print_tree_list(t_ast *ast);
void	print_tree_pipline(t_ast *ast);
void	print_tree_op(t_ast *ast);
void	free_tree_id(t_ast *ast);
void	free_tree_redir(t_ast *ast);
void	free_tree_list(t_ast *ast);
void	free_tree_pipline(t_ast *ast);
void	free_tree_op(t_ast *ast);
void	free_tree(t_ast *ast);

#endif
