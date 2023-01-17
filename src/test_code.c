#include "test_code.h"

void print_envp(t_envp *envp)
{
    t_envp *tmp;

    tmp = envp;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}