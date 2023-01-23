#include "builtin.h"

void	env(t_minishell *minishell, char **arr)
{
    print_envp(minishell);
    (void)arr;
}