#ifndef ENVP_H
# define ENVP_H

#include "types/t_envp.h"
#include <stdlib.h>

//void    init_envp(t_envp **node, char **envp);
void    get_key(t_envp *node, const char *envp);
void    get_value(t_envp *node, const char *envp);
void    insert_envp(t_envp **node, const char *key, const char *value);
void    delete_envp(t_envp **node, const char *key);
#endif
