/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:24 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:52:29 by jiwonhan         ###   ########seoul.kr  */
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

#endif
