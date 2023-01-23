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

void print_cmd_tbl(t_cmd_tbl *tbl)
{
    for (int i=0;i<tbl->cnt;i++)
    {
        printf("%s %s %d\n", tbl->cmd[i].cmd, tbl->cmd[i].opt, tbl->cmd[i].argc);
    }
}