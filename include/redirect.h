/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:58:01 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:59:08 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"
# include "types/t_redirect.h"

void		redir_lstadd_back(t_redirect **head, t_redirect *new);
t_redirect	*redir_lstnew(int type, char *value);
int			redir_dup(t_minishell *minishell);
void		handle_input_redirect(t_minishell *minishell, t_redirect *redirect);
void		handle_output_redirect(t_minishell *minishell, \
									t_redirect *redirect);
void		handle_heredoc_redirect(t_minishell *minishell, t_heredoc *heredoc);
void		handle_append_redirect(t_minishell *minishell, \
									t_redirect *redirect);
void		handle_redirects(t_minishell *minishell);
void		set_redirect(t_minishell *minishell, t_parse_tree *parse_tree);
int			redir_dup_input(t_minishell *minishell);
void		redir_dup_output_over(t_minishell *minishell);
void		redir_dup_heredoc(t_minishell *minishell);
void		redir_dup_output_append(t_minishell *minishell);

#endif