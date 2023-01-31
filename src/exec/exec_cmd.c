#include "minishell.h"
#include "exec.h"

void	run_program(t_arg *arg, char **envp)
{
	// str = arg->cmd_arg[1];
    //  built-in fnc
	// if (ft_strcmp(str, "echo") == 0)
		 
	// else if (ft_strcmp(str, "cd") == 0)

	// else if (ft_strcmp(str, "pwd") == 0)
	
    // else if (ft_strcmp(str, "export") == 0)
	
    // else if (ft_strcmp(str, "unset") == 0)
	
    // else if (ft_strcmp(str, "env") == 0)
	
    // else if (ft_strcmp(str, "exit") == 0)
	// // 내장함수
    // else
		execve(arg->cmd, arg->cmd_arg, envp); //실패하면 리턴값 -1
}

// void	logical_process(t_minishell *minishell, t_parse_tree *parse_tree)
// {
// 	minishell->exit_status = 0;
// 	get_cmd(pipe->arg, parse_tree->token->value, minishell->envp);
// 	run_program(pipe->arg, minishell->envp);
// 	// execve(arg->cmd1, arg->cmd_arg1, envp);
// 	minishell->exit_status = 1;
// 	shell_exit(1, perror("실행에러"));

// }



void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	minishell->exit_status = 0;
	if ((parse_tree->up->left == parse_tree))
	{
		get_cmd(minishell, pipe->arg, parse_tree->token->value, minishell->envp2);
		close(pipe->fd[0]);
		dup2(pipe->fd[1], STDOUT_FILENO);
		close(pipe->fd[1]);
		run_program(pipe->arg, minishell->envp2);
		// execve(pipe->arg->cmd1, pipe->arg->cmd_arg1, envp); //실패하면 리턴값 -1
	}
	else if ((parse_tree->up->right == parse_tree) && parse_tree->up->up->type == PIPE)
	{
		get_cmd(minishell, pipe->arg, parse_tree->token->value, minishell->envp2);
		close(pipe->next->fd[0]);
		dup2(pipe->next->fd[1], STDOUT_FILENO);
		close(pipe->next->fd[1]);
		run_program(pipe->arg, minishell->envp2);
		// execve(pipe->arg->cmd1, pipe->arg->cmd_arg1, envp);
	}
	minishell->exit_status = 1;
	shell_exit(minishell, 1, "error");
}

void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	(void)minishell;
	if ((parse_tree->up->left == parse_tree))
	{
		close(pipe->fd[1]);
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	}
	//up->up check할때 루트노드가 | 이면 루트의->up이 없기때문에 세그폴트 날수도있음 파서에서 루트의 up은 null로 해주면 
	// 안나는지확인
	else if ((parse_tree->up->right == parse_tree) && parse_tree->up->up->type == PIPE)
	{
		close(pipe->next->fd[1]);
		dup2(pipe->next->fd[0], STDIN_FILENO);
		close(pipe->next->fd[0]);
	}
}


void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	// execve함수하면 프로세스 종료되는거때문에 일단 구분 없앴음
	// if (parse_tree->up->type == PIPE)
	// {
		pipe->pid = fork();
		if (pipe->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipe->pid == 0)
		{
			// signal(SIGQUIT, SIG_DFL);
			child_process(minishell, parse_tree, pipe);
		}
		else
			parent_process(minishell, parse_tree, pipe);
	// }
	// else
	// 	logical_process(minishell, parse_tree);
}
