#include "minishell.h"
#include "exec.h"

void	wait_n_setexit(t_exec *exec)
{
	while (wait(&(exec->exit)) != -1)
		;
	if (exec->cmdgrpcount > 1)
		exec->exit = WEXITSTATUS(exec->exit);
}

void	pipeline(t_exec *exec, t_token *token)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;

	if (pid == 0)
	{
		close(fd[0]);
		if (exec->redirflag == 1)
			run_program(exec, token);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (exec->redirflag == 0)
			run_program(exec, token);
		exit(exec->exit);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	run_last_child(t_exec *exec, t_token *token)
{
	pid_t	pid;

	if (exec->cmdgrpcount == 1)
	{
		run_program(exec, token);
		dup2(exec->fdstdin, STDIN);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		run_program(exec, token);
		exit(exec->exit);
	}
	else
	{
		//시그널 처리?
		dup2(exec->fdstdin, STDIN);
	}
}

void	exec_line(t_minishell *exec, t_token *tok)
{
	t_token *token;
    t_exec *exec;

	token = tok;
	while (token != NULL)
	{	
		init_flags(exec);
		// if (exe_redirect(exec, token) == -1)
		// {
		// }
        //shell 명령어 잘 못 사용시
		if (exec->eofexit == 2)
		{
			reset_fd(exec, 1);
			break ;
		}
        // 실행부로 보내는 조건을 트리노드에서 루트타입으로 확인하고// left 노드를 보내는방식으로??
		if (token->next == NULL)
			run_last_child(exec, token);
        //AND, OR 따로 함수만들어서 관리 여기는 pipe 없이진행
        // else if (token->type == LOGICAL_AND || token->type == LOGICAL_OR)
        //     run_logical(exec, token);  
		else
			pipeline(exec, token);
		reset_fd(exec, 0);
		token = token->next;
	}
	wait_n_setexit(exec);
}