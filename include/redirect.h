#ifndef REDIRECT_H
# define REDIRECT_H

#include "minishell.h"
#include "types/t_redirect.h"

//here_doc.c
void	here_doc(t_minishell *minishell);

//redirect_list.c
void	redir_lstadd_back(t_redirect **head, t_redirect *new);
t_redirect	*redir_lstnew(int type, char *value);

//redirects.c
void	handle_input_redirect(t_minishell *minishell, t_redirect *redirect);
void	handle_output_redirect(t_minishell *minishell, t_redirect *redirect);
void	handle_heredoc_redirect(t_minishell *minishell, t_redirect *redirect);
void	handle_append_redirect(t_minishell *minishell, t_redirect *redirect);
void	handle_redirects(t_minishell *minishell);

# endif