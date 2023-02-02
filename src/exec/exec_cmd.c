#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "builtin.h"

void	run_program(t_arg *arg, char **envp)
{
		execve(arg->cmd, arg->cmd_arg, envp); //실패하면 리턴값 -1
}

void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	t_arg	arg;
	
	// printf("%s %s\n",parse_tree->token->value,parse_tree->token->next->value);

	// printf("%s\n",parse_tree->token->next->value);
	minishell->exit_status = 0;
	char **envp;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	if (parse_tree->up != NULL)
	{
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		close(pipe->fd[0]);
		dup2(pipe->fd[1], STDOUT_FILENO);
		close(pipe->fd[1]);
		run_program(parse_tree->token->arg, envp);
	}
	else
	{
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		run_program(parse_tree->token->arg, envp);
	}
	
	minishell->exit_status = 1;
	shell_exit(minishell, 1, "error2");
}

void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	(void)minishell;
	(void)parse_tree;
	int	status, waitpid;
	// if ((parse_tree->up->left == parse_tree))
	// {
		waitpid = wait(&status);
		(void)waitpid;
		close(pipe->fd[1]);
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	// }
	
}


void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
	char **cmds;

	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		printf(">>>exit status (%d)<<<\n", minishell->exit_status);
		while (*cmds)
			free(*cmds++);
	}
	//명령어 2개 이상일때
	else if (pipes)
	{
		pipes->pid = fork();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
			parent_process(minishell, parse_tree, pipes);
	}
	//명령어 단일로 들어왔을때
	else
	{
		int fd[2];
		pipe(fd);
		pipes = lstnew(fd);
		pipes->pid = fork();
		// printf("\n%d\n",pipes->pid);
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
		{
			int	status, waitpid;
			waitpid = wait(&status);
			(void)waitpid;
		}
		// 	parent_process(minishell, parse_tree, pipes);
	}
}
