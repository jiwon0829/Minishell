#include "minishell.h"
#include "exec.h"

void    resetfd(t_exec *exec)
{
    exec->fdin = -1;
    exec->fdout = -1; 
}

void	reset_fd(t_exec *exec, int n)
{
	if (exec->fdin > 0)
	{
		close(exec->fdin);
		if (n == 1)
			dup2(exec->fdstdin, STDIN);
	}
	if (exec->fdout > 0)
	{
		close(exec->fdout);
		dup2(exec->fdstdout, STDOUT);
	}
	// unlink("");//unlink heredoc
	resetfd(exec);
}

void	resetflags(t_exec *exec)
{
	exec->redir_flag = 0;
	exec->eof_exit = 0;
	exec->heredoc_flag = 0;
}