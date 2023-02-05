#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
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
	// printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	// printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	minishell->exit_status = 0;
	char **envp;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	if (parse_tree->up != NULL)
	{
		// printf("inchild\n");
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		close(pipe->fd[0]);
		//다음 파이프가 있고, pipe->right노드, pipe명령중일때
		if((pipe->next != NULL && pipe->right_flag == 1) && parse_tree->up->type == PIPE)
		{
			// printf("dup2 next fd[1]\n");
			dup2(pipe->next->fd[1], STDOUT_FILENO);
			// pipe = pipe->next;
			// printf("pipe!?: %d %d\n",pipe->fd[0],pipe->fd[1]);
		} 
		//현재 파이프명령중이고, pipe->left노드
		// else if(!(pipe->next == NULL && pipe->right_flag == 1) && parse_tree->up->type == PIPE)
		else if((pipe != NULL && pipe->right_flag != 1) && parse_tree->up->type == PIPE)
		{
			// printf("dup2 stout,fd[1]\n");
			dup2(pipe->fd[1], STDOUT_FILENO);
			// printf("pipe!!: %d %d\n",pipe->fd[0],pipe->fd[1]);
		}
		//마지막 실행?
		// else
		// {
			// close(pipe->fd[1]);
			// dup2(minishell->exit_fdin,STDIN_FILENO);//이건 부모에서 해야하네 마지막명령에서
			// printf("else?\n");
		// }
		close(pipe->fd[1]);
		// handle_redirects(minishell);
		run_program(parse_tree->token->arg, envp);
	}
	else
	{
		// printf("단일명령\n");
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
	
	waitpid(pipe->pid, &status, 0);
	// printf("parent\n");
	if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
		minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
	else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
		minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능
	close(pipe->fd[1]);
	dup2(pipe->fd[0], STDIN_FILENO);
	close(pipe->fd[0]);
	if((pipe->next == NULL && pipe->right_flag == 1))
	{
		// printf("dup2 복구\n");
		// printf("mini->fdstin : %d",minishell->exit_fdin);
		dup2(minishell->exit_fdin,STDIN_FILENO);//이건 부모에서 해야하네 마지막명령에서
	}
	// else if((pipe->next == NULL && pipe->right_flag == 1))
	//근데 리다이렉션있을때는 parse_tree->up->type 이 리다이렉션이네 해결해야함	

}


void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
	char **cmds;
	int status;

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
		// printf("pipee\n");
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
			// int	status, waitpid;
			// waitpid = wait(&status);
			// (void)waitpid;
			waitpid(pipes->pid, &status, 0);
			if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
				minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
			else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
				minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능

		}
		// 	parent_process(minishell, parse_tree, pipes);
	}
	/*if(pipes->right_flag == 1)
	{
		pipes = pipes->next;
		// printf("pipe move\n");
	}*/
		// printf("pipes!?: %d %d\n",pipes->fd[0],pipes->fd[1]);
}
