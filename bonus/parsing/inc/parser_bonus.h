/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 05:27:07 by asouinia          #+#    #+#             */
/*   Updated: 2022/04/23 05:47:03 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H
# include "./lexer_bonus.h"
# include "../../../libft/libft.h"
# include "./ast_bonus.h"
# include "print_tree_bonus.h"
# include <errno.h>
# include <readline/readline.h>
# include <dirent.h>

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*token;
}			t_parser;

t_parser	*parser_init_parser(t_lexer *lexer);
t_token		*parser_parser_advance(t_parser *parser, t_e_token type);
t_ast		*parser_parse(t_parser *parser);
t_ast		*parser_parse_id(t_parser *parser);
t_ast		*parser_parse_redir(t_parser *parser);
t_ast		*parser_parse_list(t_parser *parser);
t_ast		*parser_parse_pipeline(t_parser *parser);
t_ast		*parser_parse_term(t_parser *parser);
t_ast		*parser_parse_paren(t_parser *parser);
t_ast		*parser_parse_v2(t_parser *parser, t_ast *prev);
void		parser_syntax_error(char *token_value);
int			is_redir(t_token *token);
int			is_op(t_token *token);
int			here_doc(char *limiter);
t_d_list	*expand_word(char *str);
t_d_list	*expand_layer1(char *str);
char		*ft_skip_quotes(char *str, char *prev, int *i);
char		*append_char(char	*str, char c);
char		*ft_skip_var(char *str, char *prev, int *i);
char		*get_expanded_word(char *str);
char		*get_env_var(char **envp, char *env_var);
char		*append_str(char	*str, char *c);
char		*collect_str_quoted(int *i, char *str, char *prev);
int			count_stars(char *str);
char		*collect_str(int *i, char *str, int **stars_idxs);
t_d_list	*get_matches(char *pattern, int *stars_idxs);
int			is_valid_star(int idx, int *stars_idxs);
int			is_match_pattern(char *str, char *pattern, int s_p, int *stars);

#endif
