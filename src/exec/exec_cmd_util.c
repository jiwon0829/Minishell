#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"
#include "signals.h"
#include "test_code.h"

void exec_builtin(t_minishell *minishell, t_parse_tree *parse_tree)
{
	char **cmds;

	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		redir_dup(minishell);
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		while (*cmds)
			free(*cmds++);
	}
}

void exec_builtin_scmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
		exec_builtin(minishell, parse_tree);
		dup2(minishell->exit_fdin, STDIN_FILENO);//변경되었는지 체크후 실행하는거로 수정
		dup2(minishell->exit_fdout, STDOUT_FILENO);
}

void exec_multi_cmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
		pipes->pid = fork();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		set_signal(IGNORE, IGNORE);
		if (pipes->pid == 0)
		{
			child_process(minishell, parse_tree, pipes);
		}
		else
			parent_process(minishell, parse_tree, pipes);
		set_signal(CATCH, IGNORE);
}

void exec_scmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes)
{
	int status;

	int fd[2];
		pipe(fd);
		pipes = lstnew(fd);
		pipes->pid = fork();
		if (pipes->pid < 0)
			shell_err(minishell, 1, "error");
		set_signal(IGNORE, IGNORE);
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
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
		set_signal(CATCH, IGNORE);
}