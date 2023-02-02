#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"

// static int check_builtin(t_cmd_tbl *cmd_tbl, const char *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < cmd_tbl->max_element)
// 	{
// 		if (ft_strncmp(get_cmd->cmd[i].cmd, cmd, ft_strlen(cmd)) == 0)
// 			return (TRUE);
// 	}
// 	return (FALSE);
// }

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
	// 빌트인함수일때
	// if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	// {
	// 	ft_execve(minishell, minishell->cmd_tbl, cmds);
	// 	exit(1);
	// }

	//명령어 2개 이상일때
	if (pipes)
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
