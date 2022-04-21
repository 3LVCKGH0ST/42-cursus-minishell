/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:12:30 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/21 01:09:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/builder.h"

void	print_builder_pipline(t_d_list *build)
{
	t_d_list	*tmp;
	int			i;

	tmp = build;
	while (tmp)
	{
		i = -1;
		if (((t_builder *)tmp->content)->type == B_CMD)
		{
			while (((t_builder *)tmp->content)->cmd->args[++i])
			{
				printf(" %s ", ((t_builder *)tmp->content)->cmd->args[i]);
			}
			if (tmp->next)
				printf(" | ");
		}
		else
			print_builder_op((t_builder *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_builder_op(t_builder *build)
{
	print_builder(build->left);
	if (build->type == B_AND)
		printf(" && ");
	else
		printf(" || ");
	print_builder(build->right);
}

void	print_builder(t_d_list *build)
{
	t_builder	*b;

	if (!build)
		return ;
	b = (t_builder *)build->content;
	if (b->type == B_CMD)
		print_builder_pipline(build);
	else if (b->type == B_OR || b->type == B_AND)
		print_builder_op((t_builder *)build->content);
	else
		printf("ERROR print builder\n");
}

void	chartostr(char **str, char c)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = -1;
	tmp = *str;
	tmp1 = malloc(2);
	tmp1[0] = c;
	tmp1[1] = '\0';
	*str = ft_strjoin(tmp, tmp1);
	free(tmp1);
	free(tmp);
}
