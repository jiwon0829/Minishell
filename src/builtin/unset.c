#include "builtin.h"

static int check_variable_name(const char *name)
{
    if (!ft_isalpha(*name) && *name != '_')
        return (FALSE);
    while (*name)
    {
        if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
            return (FALSE);
        name++;
    }
    return (TRUE);
}

void	unset(t_minishell *minishell, char **arr)
{
    int i;

    i = 1;
    while (arr[i])
    {
        if (!check_variable_name(arr[i]))
            unset_error_message(arr[i]);
        else
            delete_envp(&(minishell->envp), arr[i]);
        ++i;
    }
}
