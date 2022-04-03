/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:50:41 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/03 00:47:28 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

t_builder	*builder_init_builder(t_builder_type type)
{
	(void)type;
	return (NULL);
}

void	ft_d_lstadd_back_v2(t_d_list **lst, t_d_list *newnode)
{
	t_d_list	*last;

	if (!newnode)
		exit(15);
	if (*lst)
	{
		last = ft_d_lstlast(*lst);
		newnode->prev = last->prev;
		last->next = newnode;
	}
	else
		*lst = newnode;
}

t_d_list	*get_tree_builder_pipline(t_ast *ast)
{
	t_d_list	*tmp;
	t_d_list	*build;

	build = NULL;
	tmp = ast->children;
	while (tmp)
	{
		if (((t_ast *)tmp->content)->type == AST_PIPELINE)
			ft_d_lstadd_back_v2(&build, \
			get_tree_builder_op((t_ast *)tmp->content));
		else
			ft_d_lstadd_back(&build, \
			ft_d_lstnew(get_tree_builder_list((t_ast *)tmp->content)));
		tmp = tmp->next;
	}
	return (build);
}

t_d_list	*get_tree_builder_op(t_ast *ast)
{
	t_builder	*build;

	build = (t_builder *)malloc(sizeof(t_builder));
	if (ast->type_token == TOKEN_AND)
		build->type = B_AND;
	if (ast->type_token == TOKEN_OR)
		build->type = B_OR;
	build->left = get_tree_builder(ast->left);
	build->right = get_tree_builder(ast->right);
	return (ft_d_lstnew(build));
}
