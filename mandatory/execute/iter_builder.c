/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/08 22:46:29 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/execute.h"

void	iter_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;
	int			i;

	tmp = build;
	while (tmp)
	{
		i = -1;
		if (((t_builder *)tmp->content)->type == B_CMD)
		{
			//while (((t_builder *)tmp->content)->cmd->args[++i])
			//{
			//	iterf(" %s ", ((t_builder *)tmp->content)->cmd->args[i]);
			//}
			//if (tmp->next)
			//	iterf(" | ");
		}
		else
			iter_builder_op((t_builder *)tmp->content);
		tmp = tmp->next;
	}
}

void	iter_builder_op(t_builder *build)
{
	iter_builder(build->left);
	if (build->type == B_AND)
		//iterf(" && ");
	else
		//iterf(" || ");
	iter_builder(build->right);
}

void	iter_builder(t_d_list *build)
{
	t_builder	*b;

	if (!build)
		return ;
	b = (t_builder *)build->content;
	if (b->type == B_CMD)
		iter_builder_pipline(build);
	else if (b->type == B_OR || b->type == B_AND)
		iter_builder_op((t_builder *)build->content);
}
