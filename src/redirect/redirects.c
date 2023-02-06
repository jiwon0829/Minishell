#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"
#include "redirect.h"

//open 실패 하면 에러처리할지? input 실패시(bash 에서 없는파일 < a 해도 에러안나옴)
void	handle_input_redirect(t_minishell *minishell, t_redirect *redirect)
{
	printf("in_input_redir\n");
	redirect->fd[0] = open(redirect->file_name, O_RDONLY);
	printf("fd : %d\n", redirect->fd[0]);
	if (redirect->fd[0] == ERR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		err_massage(minishell, 1, " No such file or directory"); //메세지 비교후 수정
		return ;
	}
	// dup2(redirect->fd[0], STDIN_FILENO);
	// close(redirect->fd[0]);
}

void	handle_output_redirect(t_minishell *minishell, t_redirect *redirect)
{
	printf("in_output_redir\n");

	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
	printf("fd : %d\n", redirect->fd[1]);
	
	if (redirect->fd[1] == ERR)
	{
		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
		return ;
	}
	
	// dup2(redirect->fd[1], STDOUT_FILENO);
	// close(redirect->fd[1]);
}

// void	handle_heredoc_redirect(t_minishell *minishell, t_heredoc *heredoc)
// {
// 	// redirect->fd[0] = open(redirect->file_name, O_RDONLY);
// 	// if (redirect->fd[0] == ERR)
// 	// {
// 	// 	err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
// 	// 	return ;
// 	// }
// 	// (void)minishell;
// 	// dup2(heredoc->fd[0], STDIN_FILENO);
// 	// close(heredoc->fd[0]);
// 	// heredoc = heredoc->next;
// }


void	handle_append_redirect(t_minishell *minishell, t_redirect *redirect)
{
	printf("in_append_redir\n");

	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (redirect->fd[1] == ERR)
	{
		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
		return ;
	}
	// dup2(redirect->fd[1], STDOUT_FILENO);
	// close(redirect->fd[1]);
}

void	handle_redirects(t_minishell *minishell)
{
	// t_redirect	*redirect;
	printf("in_handle_redir\n");
	// redirect = redir_lstnew(token->type, token->next->value);
	if(minishell->redirect)
	{
		printf("str:%s type:%d\n",minishell->redirect->file_name,minishell->redirect->type);
		printf("fd: %d fd:%d \n",minishell->redirect->fd[0],minishell->redirect->fd[1]);
	}
	while (minishell->redirect)
	{
		printf("handle_redir\n");
		// if (token->type != HERE_DOC)
		// 	redir_lstadd_back(&minishell->redirect, redirect);
		if (minishell->redirect->type == INPUT) //3
			handle_input_redirect(minishell, minishell->redirect);
		else if (minishell->redirect->type == OUTPUT_OVER)//4
			handle_output_redirect(minishell, minishell->redirect);
		else if (minishell->redirect->type == HERE_DOC)    //5
			;
			// handle_heredoc_redirect(minishell, minishell->heredoc);
		else if (minishell->redirect->type == OUTPUT_APPEND) //6
			handle_append_redirect(minishell, minishell->redirect);
		minishell->redirect = minishell->redirect->next;
	}
}

void set_redirect(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	 *tmp_token;
	t_redirect *redirect;
	printf ("in_set_redir\n");
	// t_redirect	*redirect;

	// redirect = redir_lstnew(tmp_token->type, tmp_token->next->value);
	// (void)redirect; // 이렇게 void 해도 아래에서 적용되는지 ??
	tmp_token = parse_tree->token;
	while(tmp_token)
	{
		// if (token->type != HERE_DOC)
		// 	redir_lstadd_back(&minishell->redirect, redirect);
		if (tmp_token->type == INPUT || tmp_token->type == OUTPUT_OVER || \
			tmp_token->type == HERE_DOC || tmp_token->type == OUTPUT_APPEND)
		{
			redirect = redir_lstnew(tmp_token->type, tmp_token->next->value);
			// printf("check redir type :%d\n", minishell->redirect->type);
			if (tmp_token->type == INPUT) //3
				handle_input_redirect(minishell, redirect);
			else if (tmp_token->type == OUTPUT_OVER)//4
				handle_output_redirect(minishell, redirect);
			else if (tmp_token->type == HERE_DOC)    //5
				;
			else if (tmp_token->type == OUTPUT_APPEND) //6
				handle_append_redirect(minishell, redirect);
			// printf("fd : %d\n", redirect->fd[0]);
			printf("here_fd: %d\n",minishell->heredoc->fd[0]);
			// printf("fd : %d\n", redirect->fd[1]);
			//redire (reset되었는지) 비어있는지 체크
			if (minishell->redirect)
				printf("before str%s\n",minishell->redirect->file_name);
			else
				printf("redire empty\n");
			redir_lstadd_back(&(minishell->redirect), redirect);
			//printf("lstadd fd: %d\n",minishell->redirect->fd[0]);
			tmp_token = tmp_token->next->next;
		}
		else
		{
			printf("set redir else\n");
			tmp_token = tmp_token->next;
		}
	}
	printf("ff\n");
	// while(minishell->redirect)
	// {
	// 	// printf("redir type :%d\n", minishell->redirect->type);
	// 	printf("fd[0] :%d\n", minishell->redirect->fd[0]);
	// 	printf("fd[1]  :%d\n", minishell->redirect->fd[1]);

	// 	minishell->redirect = minishell->redirect->next;
	// }
	// printf("ffqq\n");

	// while(tmp_token)
	// {
	// 	if (tmp_token->type == INPUT || tmp_token->type == OUTPUT_OVER || \
	// 		tmp_token->type == HERE_DOC || tmp_token->type == OUTPUT_APPEND)
	// 	{
	// 		redir_lstadd_back (&(minishell->redirect), redir_lstnew(tmp_token->type, tmp_token->next->value));
	// 		tmp_token = tmp_token->next->next;
	// 		// handle_redirects(minishell, tmp_token);
	// 	printf ("in_set_redir while\n");
	// 	}
	// 	else
	// 		tmp_token = tmp_token->next;
		
	// }
}
