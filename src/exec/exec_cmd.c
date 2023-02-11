#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"
#include "term_signal.h"
#include "test_code.h"

static void exec_builtin(t_minishell *minishell, t_parse_tree *parse_tree)
{
	char **cmds;

	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		redir_dup(minishell, minishell->redirect);
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		printf(">>>exit status (%d)<<<\n", minishell->exit_status);
		while (*cmds)
			free(*cmds++);
	}
}

void	run_program(t_arg *arg, char **envp)
{
	execve(arg->cmd, arg->cmd_arg, envp); //실패하면 리턴값 -1
}

void	child_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	t_arg	arg;
	char **envp;

	minishell->exit_status = 0;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	// 파이프나 and or 이 있을때
	if (parse_tree->up != NULL)
	{
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		if (parse_tree->token == NULL)
			exit (0);	
		// 파이프 라인에서 중간노드
		if((pipe->next != NULL && pipe->right_flag == 1) && parse_tree->up->type == PIPE && parse_tree->up->up->type == PIPE)
		{
			dup2(pipe->next->fd[1], STDOUT_FILENO);
		} 
		// 파이프 라인에서 제일처음노드
		else if((pipe && pipe->right_flag != 1) && parse_tree->up->type == PIPE)
		{
			close(pipe->fd[0]);
			dup2(pipe->fd[1], STDOUT_FILENO);
			close(pipe->fd[1]);
		}
		//마지막 실행 (파이프라인에서 마지막노드)
		else
		{
			close(pipe->fd[1]);
		}
		redir_dup(minishell, minishell->redirect);
		if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
		{
			exec_builtin(minishell, parse_tree);
			exit(minishell->exit_status);
		}
		else
			run_program(parse_tree->token->arg, envp);
	}
	// printf("단일명령\n");
	else
	{
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		if (parse_tree->token == NULL)
			exit (0);	
		redir_dup(minishell, minishell->redirect);//redirect 반영
		if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
		{
			exec_builtin(minishell, parse_tree);
			exit(minishell->exit_status);
		}
		else
			run_program(parse_tree->token->arg, envp);
	}
	minishell->exit_status = 1;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse_tree->token->value, 2);
	shell_exit(minishell, 1, ": command not found");
}

void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	(void)minishell;
	(void)parse_tree;
	int	status;
	
	waitpid(pipe->pid, &status, 0);//이건 병렬적 실행을해야해서 변경예정
	if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
		minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
	else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
		minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능
	// 다음 파이프가 있어서 다음파이프로 stdin재설정
	if (parse_tree->up && parse_tree->up->up && parse_tree->up->up->type == PIPE && pipe->right_flag == 1)
	{
		dup2(pipe->next->fd[0], STDIN_FILENO);
		close(pipe->next->fd[1]);
		close(pipe->next->fd[0]);
		// close(pipe->next->fd[1]);
	}
	// 마지막 명령 STDIN 원래대로 복구
	else if ( pipe->right_flag == 1 && (!parse_tree->up || !parse_tree->up->up || (parse_tree->up->up && parse_tree->up->up->type != PIPE)) )
	{
		dup2(minishell->exit_fdin, STDIN_FILENO);
	}
	//왼쪽 처음노드
	else
	{
		close(pipe->fd[1]);
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	}
	minishell->redirect = NULL;//free redirect해야함, 리다이렉션 초기화
}

void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
	// char **cmds;
	int status;

	set_redirect(minishell, parse_tree);//리다이렉션 체크후 리스트만생성
	set_cmd(minishell, parse_tree);//리다이렉션 제거된 토큰으로 주소이동
	// 빌트인함수,단일명령 일때
	if ((parse_tree->up == NULL && check_builtin(minishell->cmd_tbl, parse_tree->token->value)) 
		|| (pipes && parse_tree->up->type != PIPE))
	{
		exec_builtin(minishell, parse_tree);
		dup2(minishell->exit_fdin, STDIN_FILENO);//변경되었는지 체크후 실행하는거로 수정
		dup2(minishell->exit_fdout, STDOUT_FILENO);
	}
	//명령어 2개 이상일때
	else if (pipes)
	{
		pipes->pid = fork();
		setting_child();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
			parent_process(minishell, parse_tree, pipes);
		setting_signal();
	}
	//명령어 단일로 들어왔을때
	else
	{
		int fd[2];
		pipe(fd);
		pipes = lstnew(fd);
		pipes->pid = fork();
		setting_child();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
		{
			waitpid(pipes->pid, &status, 0);
			if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
				minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
			else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
				minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능
		}
		setting_signal();
	}
	if(pipes && pipes->right_flag == 1)
	{
		pipes = pipes->next;
	}
}
