/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:24 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 19:10:39 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "expander.h"
# include "expander.h"
# include "t_expander.h"

void	expander(t_minishell *minishell, t_parse_tree *parse_tree);
void	remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, \
						int *i);
int		remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, \
					int *i, int check);
void	remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, \
						int *i);
char	*expen_strjoin(char *s1, char *s2);
char	*expand_substr(char const *s, unsigned int start, size_t len);
void	expand_exit_status(t_minishell *minishell, t_parse_tree *parse_tree, \
							int *i, int j);
void	init_expander(t_expander *expander);
void	expand_dollor(t_minishell *minishell, t_expander *expander, \
					t_parse_tree *parse_tree, int *i);
void	is_split_token(t_parse_tree *parse_tree, int start, int *end);
int		wildcard(t_token *token);
int		quote_delete(t_token *token, int is_expand);
int		envp_expand(t_minishell *minishell, t_token *token, int *is_expand);
int		find_type(char *str);
void	get_char_type(char *str, int *check);
void	find_envp_key(int *check, int len);
void	change_word_all(int *check, int start, int end);
void	change_single_quote(int *check, int start, int end);
int		quote_in_envp(char *str, int *check);
void	get_delete_char_string(char *str, int *check, char *ret, int len);
void	change_exit_status_value(t_minishell *minishell, char **ret, \
								int *now_len, int *i);
char	*get_key_in_string(int *check, char *str, int *i);
void	change_value(char **ret, char *key, char *value, int *now_len);
void	change_envp_value(t_minishell *minishell, t_token *token, \
						int *check, char **ret);

#endif
