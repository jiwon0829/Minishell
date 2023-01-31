#include "minishell.h"
#include "error_message.h"
#include "exec.h"

void shell_err(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	err_massage(minishell, status, msg);
	
}

void shell_exit(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	exit_err_massage(minishell, status, msg);
}