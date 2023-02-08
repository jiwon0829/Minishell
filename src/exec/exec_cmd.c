#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"
#include "test_code.h"

void	run_program(t_arg *arg, char **envp)
{
	printf("---in runprogram---\n");
		execve(arg->cmd, arg->cmd_arg, envp); //실패하면 리턴값 -1
}

void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	t_arg	arg;
	char **envp;
	set_redirect(minishell, parse_tree);

	printf("=-=-==-=--=-=-=-=-=-=-==--=\n");
	printf("---in child proc---\n");

	// printf("%s %s\n",parse_tree->token->value,parse_tree->token->next->value);

	// printf("%s\n",parse_tree->token->next->value);
	// printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	// printf("pipe_leftflag: %d pipe_rightflag : %d\n", pipe->left_flag, pipe->right_flag);
	
	printf ("\n\n$$$$$$$$$$$$$$$$\n");
	printf("pip->right_flag: %d\n", pipe->right_flag);
	if (parse_tree->up)
		printf("pip->up->type: %d\n", parse_tree->up->type);

	minishell->exit_status = 0;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	// 파이프나 and or 이 있을때
	if (parse_tree->up != NULL)
	{
		// printf("inchild\n");
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		if (parse_tree->token == NULL)
			exit (0);
		//파이프 있고 오른쪽노드일때 읽기 변경
		// if (parse_tree->up && parse_tree->up->type == PIPE && pipe->right_flag == 1)
		// {
		// 	printf("dup2 pipe_fd[0],STDIN\n");
		// 	// int ret = dup2(pipe->fd[0], STDIN_FILENO);
		// 	// printf("dup2 ret = %d \n",ret);
		// 	// close(pipe->fd[0]);

		// }
		// else
			// close(pipe->fd[0]);
		// printf("close fd[0]!?!?!?\n");	
		//다음 파이프가 있고, pipe->right노드, pipe명령중일때((오른쪽)) 쓰기변경
		if((pipe->next != NULL && pipe->right_flag == 1) && parse_tree->up->type == PIPE && parse_tree->up->up->type == PIPE)
		{
			// printf("dup2 next fd[1]\n");
			printf("\n\n$$$$$$$$$$$$$$$2\n\n");
			dup2(pipe->next->fd[1], STDOUT_FILENO);
			// close(pipe->next->fd[1]);


			// pipe = pipe->next;
			// printf("pipe!?: %d %d\n",pipe->fd[0],pipe->fd[1]);
		} 
		//현재 파이프명령중이고, pipe->left노드 ((왼쪽))
		// else if(!(pipe->next == NULL && pipe->right_flag == 1) && parse_tree->up->type == PIPE)
		else if((pipe && pipe->right_flag != 1) && parse_tree->up->type == PIPE)
		{
			// printf("dup2 stout,fd[1]\n");
			// int ret;
			// char c;

			// ret = 
			printf("\n\n$$$$$$$$$$$$$$$1\n\n");
			close(pipe->fd[0]);
			dup2(pipe->fd[1], STDOUT_FILENO);
			close(pipe->fd[1]);
			// c = ret + 48;
			// write(minishell->exit_fdout, "%%%%%", 5);

			// write(minishell->exit_fdout, &c, 4);

			// printf("pipe!!: %d %d\n",pipe->fd[0],pipe->fd[1]);
		}
		//마지막 실행 오른쪽
		else
		{
			printf("close fd[1]!?!?!?\n");
			close(pipe->fd[1]);
			// close(pipe->fd[0]);

			// dup2(minishell->exit_fdin,STDIN_FILENO);//이건 부모에서 해야하네 마지막명령에서
			// printf("else?\n");
		}
		// close(pipe->fd[1]);
		// handle_redirects(minishell);
		redir_dup(minishell, minishell->redirect);
		print_redir_list(minishell->redirect);
		printf("\n>>>>>last set redir fd<<<<<\n");
		if (minishell->redirect)
			printf("%d %d\n", minishell->redirect->fd[0], minishell->redirect->fd[1]);
		printf("------------------------------\n");
		run_program(parse_tree->token->arg, envp);
	}
	else
	{
		// printf("단일명령\n");
		printf("exec_cmd_else(단일명령)\n");
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		// handle_redirects(minishell);
	// if (minishell->redirect)
	// {
	// 	printf("fd : %d\n",minishell->redirect->fd[0]);
	// 	printf("fd : %s\n",minishell->redirect->file_name);
	// }
		redir_dup(minishell, minishell->redirect);

		// if (parse_tree->token)

		run_program(parse_tree->token->arg, envp);
	}
	
	minishell->exit_status = 1;
	printf("---finish child proc---(run program fail)\n");
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
	//모두 자식프로세스에서진행하는걸로 변경
	// close(pipe->fd[1]);
	// dup2(pipe->fd[0], STDIN_FILENO);
	// close(pipe->fd[0]);

	// printf("this parent proc\n");
	// if((pipe->right_flag == 1 && pipe->next == NULL ) ||(parse_tree->up->up && (parse_tree->up->up->type != PIPE )))
	// {
	// 	close(pipe->fd[1]);
	// 	close(pipe->fd[0]);

	// // 	// printf("dup2 복구\n");
	// // 	// printf("mini->fdstin : %d",minishell->exit_fdin);
	// // 	dup2(minishell->exit_fdin,STDIN_FILENO);//이건 부모에서 해야하네 마지막명령에서
	// // 	printf ( "change stdin std\n");
	// }

	// close(minishell->redirect->fd[0]);
	// close(minishell->redirect->fd[1]);

	// if (pipe->next && pipe->right_flag == 1)
	if (parse_tree->up && parse_tree->up->up && parse_tree->up->up->type == PIPE && pipe->right_flag == 1)
	{
		printf("#################1\n");

		dup2(pipe->next->fd[0], STDIN_FILENO);
		close(pipe->next->fd[1]);
		close(pipe->next->fd[0]);
		// close(pipe->next->fd[1]);
	}
	// 마지막 파이프종료시점이라 STDIN원래대로 복구
	else if ( pipe->right_flag == 1 && (!parse_tree->up || !parse_tree->up->up || (parse_tree->up->up && parse_tree->up->up->type != PIPE)) )
	{
		printf("#################2\n");
		dup2(minishell->exit_fdin, STDIN_FILENO);
		// close(pipe->fd[1]);
	}
	//왼쪽 처음1번
	else
	{
		// dup2(pipe->fd[1], minishell->exit_fdout);
		printf("#################3\n");
		printf("fd0 : %d fd1 : %d \n",pipe->fd[0],pipe->fd[1]);
		printf("fd[1] : %d\n",pipe->fd[1]);
		close(pipe->fd[1]);
		printf("fd[1] : %d\n",pipe->fd[1]);

		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	}

	minishell->redirect = NULL;//free redirect

	// else if((pipe->next == NULL && pipe->right_flag == 1))
	//근데 리다이렉션있을때는 parse_tree->up->type 이 리다이렉션이네 해결해야함	

}

void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
	char **cmds;
	int status;

	set_redirect(minishell, parse_tree);
	print_redir_list(minishell->redirect);

	// print_redir_list(minishell->redirect);
	// set_cmd(minishell, parse_tree);
	if (minishell->redirect)
		printf("===(after set_red,dmc) check cur first redir str:%s===\n", minishell->redirect->file_name);
	// while (parse_tree->token)
	// {
	// 	printf("set_cmd: %s \n",parse_tree->token->value);
	// 	parse_tree->token = parse_tree->token->next;
	// }
	printf("after set cmd(((실행 토큰없으면 NULL출력)))\n");
	if (parse_tree->token == NULL)
	{
		printf("token is NULL\n");
		return ;
	}
	// if (parse_tree->up && parse_tree->up->type == PIPE && pipes->right_flag == 1)
	// 	{
	// 		printf("dup2 pipe_fd[0],STDIN\n");
	// 		dup2(pipes->fd[0], STDIN_FILENO);
	// 	}

	// printf("cmd : %s\n", parse_tree->token->value);
	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		printf(">>>exit status (%d)<<<\n", minishell->exit_status);
		while (*cmds)
			free(*cmds++);
	}
	//명령어 2개 이상일때
	// if (pipes)
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
			// parent_process(minishell, parse_tree, pipes);
		}
	}
	if(pipes && pipes->right_flag == 1)
	{
		pipes = pipes->next;
		// printf("pipe move\n");
	}
	// close(minishell->redirect->fd[0]);
	// close(minishell->redirect->fd[1]);

	// if (pipes == NULL)
	// 	dup2(minishell->exit_fdin, STDIN_FILENO);
		// printf("pipes!?: %d %d\n",pipes->fd[0],pipes->fd[1]);
}
