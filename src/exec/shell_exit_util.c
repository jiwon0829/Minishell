#include "minishell.h"
#include "exec.h"
#include "error_message.h"

void	redir_open_error_message(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (minishell->scmd_builtin == 0)
		exit (minishell->exit_status);
}

void	permission_error_message(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	if (minishell->scmd_builtin == 0)
		exit (minishell->exit_status);
}