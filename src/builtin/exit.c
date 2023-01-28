#include "builtin.h"

int is_valid_value(char **arr)
{
    if (!arr[1])
        return (EXIT_NO);
    if (!ft_isalnum(arr[1]))
        return (EXIT_NON_NUM);
    if (arr[2])
        return (EXIT_MANY);
    return (ft_atoi(arr[1]));
}

void    exit_message(int status)
{
    printf("exit\n");
    exit(status);
}

void    ft_exit(t_minishell *minishell, char **arr)
{
    int state;

    state = is_valid_value(arr);
    if (state == EXIT_NO)
        exit_message(minishell->exit_status);
    else if (state == EXIT_NON_NUM)
    {
        printf("non numberic\n");
        exit(255);
    }
    else if(state == EXIT_MANY)
        exit_message(EXIT_MANY);
    else
        exit_message(state);
}
