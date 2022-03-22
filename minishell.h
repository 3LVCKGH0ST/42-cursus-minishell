/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalagui <mbalagui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:30:59 by mbalagui          #+#    #+#             */
/*   Updated: 2022/03/22 16:47:13 by mbalagui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

void	readinputs(char **read);
size_t	ft_strlen(const char *c);
int		skiplfspace(char *str, int defaultval);
int		skiprtspace(char *str);
char	**split_cmds(char *line);
int		quotescheckers(char *str, int end);
int		*get_pipe_idxs(char *line);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strdup_v2(char *s1, int idx_start, int idx_end);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		emptypipes(char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_echo(char *str);
char	**ft_split(char const *s, char c);

#endif