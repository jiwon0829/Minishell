#include "minishell.h"
#include "exec.h"

int	ft_execve(exec *exec, t_token *token, char *value)
{
	pid_t	pid;
	char	**args;
	char	*path;
	int		status;

	pid = fork();
	if (pid == 0)
	{
        //시그널처리
		args = argarr(exec, token);
		path = get_command_path(exec, token->value, 0);
		// execve(value, args, exec->sh_env);
		if (execve(path, args, exec->sh_env) == -1)
			exit(NOCOMMAND); // NOCOMMAND : 127
		exit(exec->exit);
	}
	else
	{
        //시그널처리
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == NOCOMMAND)
			print_error(exec, "Error. Command not found\n", NOCOMMAND);
		return (WEXITSTATUS(status));
	}
}