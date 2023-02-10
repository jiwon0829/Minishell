#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"
#include "expander.h"

//expender.c
void expander(t_minishell *minishell, t_parse_tree *parse_tree);
void remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);
void remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, int *i);
void remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);

#endif