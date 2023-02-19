#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"
#include "expander.h"
#include "expander.h"
#include "t_expander.h"

//expander.c
void expander(t_minishell *minishell, t_parse_tree *parse_tree);
void remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);
int remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, int *i, int check);
void remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i);

//expander_util.c
char	*expen_strjoin(char *s1, char *s2);
char	*expand_substr(char const *s, unsigned int start, size_t len);
void expand_exit_status(t_minishell *minishell, t_parse_tree *parse_tree, int *i, int j);
void init_expander(t_expander *expander);
void expand_dollor(t_minishell *minishell, t_expander *expander, t_parse_tree *parse_tree, int *i);

//expander_dollor_util.c
void	is_split_token(t_parse_tree *parse_tree, int start, int *end);

//wildcard
int	wildcard(t_token *token);

//quote
int quote_delete(t_token *token);

#endif
