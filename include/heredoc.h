#ifndef HEREDOC_H
# define HEREDOC_H

#include "minishell.h"
#include "types/t_heredoc.h"

//heredoc.c
void heredoc_child(t_minishell *minishell, t_heredoc *heredoc, t_token *token);
void open_heredoc(t_minishell *minishell, t_token *token);
void check_heredoc(t_minishell *minishell, t_parse_tree *parse_tree);
void exec_heredoc(t_minishell *minishell, t_parse_tree *parse_tree);

//heredoc_util.c
t_heredoc *init_heredoc(t_minishell *minishell);
void	heredoc_add_back(t_heredoc **head, t_heredoc *new);

#endif