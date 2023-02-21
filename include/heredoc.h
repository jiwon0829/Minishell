/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:52:55 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:54:28 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "types/t_heredoc.h"
# include "t_expander.h"

void		heredoc_child(t_minishell *minishell, t_heredoc *heredoc, \
						t_token *token);
void		open_heredoc(t_minishell *minishell, t_token *token);
void		check_heredoc(t_minishell *minishell, t_parse_tree *parse_tree);
void		exec_heredoc(t_minishell *minishell, t_parse_tree *parse_tree);
t_heredoc	*init_heredoc(t_minishell *minishell);
void		heredoc_add_back(t_heredoc **head, t_heredoc *new);
int			heredoc_strncmp(const char *s1, const char *s2, size_t n);
void		heredoc_remove_squotes(t_minishell *minishell, char **value, \
									int *i);
void		heredoc_remove_dquotes(t_minishell *minishell, char **value, \
									int *i);
char		*heredoc_expander(t_minishell *minishell, t_heredoc *heredoc, \
							char *value);
void		*heredoc_dollor_expander(t_minishell *minishell, \
									t_heredoc *heredoc, char **value);
int			heredoc_remove_dollor(t_minishell *minishell, char **value, int *i);
void		heredoc_expand_exit_status(t_minishell *minishell, char **value, \
										int *i, int j);
void		check_limit(t_minishell *minishell, t_heredoc *heredoc, \
						t_token *token);
void		heredoc_expand_dollor(t_minishell *minishell, t_expander *expan, \
									char **value, int *i);

#endif
