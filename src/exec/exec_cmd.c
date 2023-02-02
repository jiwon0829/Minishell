#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"

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
	printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	// printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	minishell->exit_status = 0;
	char **envp;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	if (parse_tree->up != NULL)
	{
		printf("inchild\n");
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		close(pipe->fd[0]);
		if((pipe->next != NULL && pipe->right_flag == 1) && parse_tree->type == PIPE)
		{
			printf("dup2 next fd[1]\n");
			dup2(pipe->next->fd[1], STDOUT_FILENO);
			// pipe = pipe->next;
			// printf("pipe!?: %d %d\n",pipe->fd[0],pipe->fd[1]);
		} 
		else if(!(pipe->next == NULL && pipe->right_flag == 1) && parse_tree->type == PIPE)
		{
			printf("dup2 stout,fd[1]\n");
			dup2(pipe->fd[1], STDOUT_FILENO);
			// printf("pipe!!: %d %d\n",pipe->fd[0],pipe->fd[1]);
		}
		else
			printf("else?\n");
		close(pipe->fd[1]);
		run_program(parse_tree->token->arg, envp);
	}
	else
	{
		printf("단일명령\n");
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
	int	status;
	// if ((parse_tree->up->left == parse_tree))
	// {
		// waitpid = wait(&status);
		waitpid(pipe->pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->exit_status = WTERMSIG(status);
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
	// while(pipes)
	// {
	// 	printf("pipes on\n");
	// 	pipes= pipes->next;
	// }
	// printf("pipe!: %d %d\n",pipes->fd[0],pipes->fd[1]);
	// if (pipes->left_flag == 1)
	// 	pipes->right_flag = 1;
	// if (pipes->left_flag != 1)
	// 	pipes->left_flag = 1;

	if (pipes)
	{
		printf("pe\n");
		pipes->pid = fork();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
			parent_process(minishell, parse_tree, pipes);
		// printf("pipe change\n");
		// pipes = pipes->next;
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
	if(pipes->right_flag == 1)
	{
		pipes = pipes->next;
	}
		// printf("pipes!?: %d %d\n",pipes->fd[0],pipes->fd[1]);
}
