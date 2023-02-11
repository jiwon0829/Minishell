#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"
#include "expander.h"

//expander.c
void expander(t_minishell *minishell, t_parse_tree *parse_tree);
void remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);
int remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, int *i);
void remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);

//expander_util.c
void expand_exit_status(t_minishell *minishell, t_parse_tree *parse_tree, int *i, int j);

#endif