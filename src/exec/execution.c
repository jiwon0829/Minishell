#include "minishell.h"
#include "exec.h"

void	run_program(t_exec *exec, t_token *token)
{
	str = token->value;
    //  built-in fnc
	if (ft_strcmp(str, "echo") == 0)
		 
	else if (ft_strcmp(str, "cd") == 0)

	else if (ft_strcmp(str, "pwd") == 0)
	
    else if (ft_strcmp(str, "export") == 0)
	
    else if (ft_strcmp(str, "unset") == 0)
	
    else if (ft_strcmp(str, "env") == 0)
	
    else if (ft_strcmp(str, "exit") == 0)
	// 내장함수
    else
		exec->exit = ft_execve(exec, token, str);
}

void	execution(t_minishell *minishell, t_token *token)
{
    //히어독 2개있을때 내용저장 어떻게할지 ex) cat << a | grep a && cat<< b | grep b
	//run_heredocs(shell, grp); 
	if (minishell->exit == 0)
		exec_line(minishell, token);
}
