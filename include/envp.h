#ifndef ENVP_H
# define ENVP_H

#include <stdlib.h>
#include "minishell.h"
#include "types/t_envp.h"

//void    init_envp(t_envp **node, char **envp);
void    get_key(t_envp *node, const char *envp);
void    get_value(t_envp *node, const char *envp);
void    insert_envp(t_envp **node, const char *key, const char *value);
void    delete_envp(t_envp **node, const char *key);
t_envp *get_envpNode(t_envp *head, const char *key);

void    print_envp(t_minishell *minishell);
void	print_sort_envp(t_minishell *minishell);

#endif
