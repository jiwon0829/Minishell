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

void redir_dup_input(t_minishell *minishell)
{
	int ret;
	minishell->redirect->fd[0] = open(minishell->redirect->file_name, O_RDONLY);
	ret = dup2(minishell->redirect->fd[0], STDIN_FILENO);
	//이런식으로 dup2실패하는지 체크해서 에러처리 하면좋을듯 리다이렉션전체
	if (ret == -1)
	{
		perror("dup2");
		// printf("errno : %d open failed : %s\n",errno, strerror(errno));
		
	}
	close(minishell->redirect->fd[0]);
}

void redir_dup_output_over(t_minishell *minishell)
{
	minishell->redirect->fd[1] = open(minishell->redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	dup2(minishell->redirect->fd[1], STDOUT_FILENO);close(minishell->redirect->fd[1]);
}
void redir_dup_heredoc(t_minishell *minishell)
{
	dup2(minishell->heredoc->fd[0], STDIN_FILENO);
	close(minishell->heredoc->fd[0]);
	minishell->heredoc = minishell->heredoc->next;
}

void redir_dup_output_append(t_minishell *minishell)
{
	minishell->redirect->fd[1] = open(minishell->redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
	dup2(minishell->redirect->fd[1], STDOUT_FILENO);
	close(minishell->redirect->fd[1]);
}
