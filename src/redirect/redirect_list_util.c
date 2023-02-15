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

int redir_dup_input(t_minishell *minishell)
{
	int ret;

	minishell->redirect->fd[0] = open(minishell->redirect->file_name, O_RDONLY);
	ret = dup2(minishell->redirect->fd[0], STDIN_FILENO);
	//이런식으로 dup2실패하는지 체크해서 에러처리 하면좋을듯 리다이렉션전체
	close(minishell->redirect->fd[0]);
	if (minishell->redirect->fd[0] == -1)
	{
		if (minishell->scmd_builtin == 1)
			{
				redir_open_error_message(minishell, 1, minishell->redirect->file_name);
				return (-1);
			}
		redir_open_error_message(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
	return (1);
}

void redir_dup_output_over(t_minishell *minishell)
{
	int	ret;

	minishell->redirect->fd[1] = open(minishell->redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	ret = dup2(minishell->redirect->fd[1], STDOUT_FILENO);
	close(minishell->redirect->fd[1]);
	if (minishell->redirect->fd[1] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}
void redir_dup_heredoc(t_minishell *minishell)
{
	int	ret;

	ret = dup2(minishell->heredoc->fd[0], STDIN_FILENO);
	close(minishell->heredoc->fd[0]);
	minishell->heredoc = minishell->heredoc->next;
	if (minishell->redirect->fd[0] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}

void redir_dup_output_append(t_minishell *minishell)
{
	int ret;

	minishell->redirect->fd[1] = open(minishell->redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
	ret = dup2(minishell->redirect->fd[1], STDOUT_FILENO);
	close(minishell->redirect->fd[1]);
	if (minishell->redirect->fd[1] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}
