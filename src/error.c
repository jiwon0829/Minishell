#include "minishell.h"

void    print_error(t_exec *exec, char *message, int errtype)
{
    ft_putstr_fd(message, 2);
    exec->exit = errtype;
}