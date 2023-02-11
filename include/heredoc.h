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

//heredoc_expand.c
void heredoc_remove_squotes(t_minishell *minishell, char **value, int *i);
void heredoc_remove_dquotes(t_minishell *minishell, char **value, int *i);
char *heredoc_expander(t_minishell *minishell, t_heredoc *heredoc, char *value);
void *heredoc_dollor_expander(t_minishell *minishell, t_heredoc *heredoc, char **value);
int heredoc_remove_dollor(t_minishell *minishell, char **value, int *i);

//heredoc_expand_util.c
void heredoc_expand_exit_status(t_minishell *minishell, char **value, int *i, int j);



#endif