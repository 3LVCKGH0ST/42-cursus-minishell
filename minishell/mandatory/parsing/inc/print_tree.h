/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:28:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/30 19:31:38 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TREE_H
# define PRINT_TREE_H
# include "parser.h"
void	print_tree_list(t_ast *ast);
void	print_tree_pipline(t_ast *ast);
void	print_tree(t_ast *ast);
void	print_tree_paren(t_ast *ast);
void	print_tree_op(t_ast *ast);
#endif
