#include "minishell.h"
#include "exec.h"

void	exec_logical(t_minishell *exec, t_token *tok)
{
    if(token->type == LOGICAL_AND)
    {
        // args=tok->value
        if (execve(path, args, exec->sh_env) == -1)
            exit(NOCOMMAND); // NOCOMMAND : 127
        //args=tok->next->next->value
        else
            execve(path, args, exec->sh_env);
    }
    else
    {
        // args=tok->value
        if (execve(path, args, exec->sh_env) == 0)
            exit(NOCOMMAND); // NOCOMMAND : 127
        //args=tok->next->next->value
        else
            execve(path, args, exec->sh_env);
    }

}