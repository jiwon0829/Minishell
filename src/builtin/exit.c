#include "builtin.h"
#include "error_message.h"

int is_valid_value(char **arr)
{
    int i;

    if (!arr[1])
        return (EXIT_NO);
    if (arr[2])
        return (EXIT_MANY);
    i = 0;
    while (arr[1][i])
        if (!ft_isdigit(arr[1][i++]))
            return (EXIT_NON_NUM);
    i = ft_atoi(arr[1]);
    //if (i == 0)
    //    return (EXIT_NON_NUM);
    return (i);
}

void    ft_exit(t_minishell *minishell, char **arr)
{
    int state;

    state = is_valid_value(arr);
    if(state == EXIT_MANY)
    {
        exit_argment_cnt_error();
        minishell->exit_status = 255;
        return ;
    }
    else if (state == EXIT_NON_NUM)
    {
        exit_argment_error(arr[1]);
        minishell->exit_status = 255;
    }
    else if (state == EXIT_NO)
    {
        ft_putstr_fd("exit\n", 2);
        minishell->exit_status = 0;
    }
    else
    {
        ft_putstr_fd("exit\n", 2);
        minishell->exit_status = state;
    }
    exit(minishell->exit_status);
}
