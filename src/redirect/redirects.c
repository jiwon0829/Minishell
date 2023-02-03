#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"

//open 실패 하면 에러처리할지? input 실패시(bash 에서 없는파일 < a 해도 에러안나옴)
void	handle_input_redirect(t_minishell *minishell, t_redirect *redirect)
{
	redirect->fd[0] = open(redirect->file_name, O_RDONLY);
	if (redirect->fd[0] == ERR)
	{
		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
		return ;
	}
	dup2(redirect->fd[0], STDIN_FILENO);
	close(redirect->fd[0]);
}

void	handle_output_redirect(t_minishell *minishell, t_redirect *redirect)
{
	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	{
		if (redirect->fd[1] == ERR)
		{
			err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
			return ;
		}
	}
	dup2(redirect->fd[1], STDOUT_FILENO);
	close(redirect->fd[1]);
}

void	handle_heredoc_redirect(t_minishell *minishell, t_redirect *redirect)
{
	redirect->fd[0] = open(redirect->file_name, O_RDONLY);
	if (redirect->fd[0] == ERR)
	{
		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
		return ;
	}
	dup2(redirect->fd[0], STDIN_FILENO);
	close(redirect->fd[0]);
}


void	handle_append_redirect(t_minishell *minishell, t_redirect *redirect)
{
	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (redirect->fd[1] == ERR)
	{
		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
		return ;
	}
	dup2(redirect->fd[1], STDOUT_FILENO);
	close(redirect->fd[1]);
}

void	handle_redirects(t_minishell *minishell)
{
	while(minishell->redirect)
	{
		if (minishell->redirect->type == INPUT) //3
			handle_input_redirect(minishell, minishell->redirect);
		else if (minishell->redirect->type == OUTPUT_OVER)//4
			handle_output_redirect(minishell, minishell->redirect);
		else if (minishell->redirect->type == HERE_DOC)    //5
			handle_heredoc_redirect(minishell, minishell->redirect);
		else if (minishell->redirect->type == OUTPUT_APPEND) //6
			handle_append_redirect(minishell, minishell->redirect);
		minishell->redirect = minishell->redirect->next;
	}
}