#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"
#include "redirect.h"

// //open 실패 하면 에러처리할지? input 실패시(bash 에서 없는파일 < a 해도 에러안나옴)
// void	handle_input_redirect(t_minishell *minishell, t_redirect *redirect)
// {
// 	redirect->fd[0] = open(redirect->file_name, O_RDONLY);
// 	if (redirect->fd[0] == ERR)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(redirect->file_name, 2);
// 		err_massage(minishell, 1, " No such file or directory"); //메세지 비교후 수정
// 		return ;
// 	}
// }

// void	handle_output_redirect(t_minishell *minishell, t_redirect *redirect)
// {
// 	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	
// 	if (redirect->fd[1] == ERR)
// 	{
// 		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
// 		return ;
// 	}
// }

// void	handle_append_redirect(t_minishell *minishell, t_redirect *redirect)
// {
// 	redirect->fd[1] = open(redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
// 	if (redirect->fd[1] == ERR)
// 	{
// 		err_massage(minishell, 1, redirect->file_name); //메세지 비교후 수정
// 		return ;
// 	}
// }

// void	handle_redirects(t_minishell *minishell)
// {
// 	while (minishell->redirect)
// 	{
// 		if (minishell->redirect->type == INPUT) //3
// 			handle_input_redirect(minishell, minishell->redirect);
// 		else if (minishell->redirect->type == OUTPUT_OVER)//4
// 			handle_output_redirect(minishell, minishell->redirect);
// 		else if (minishell->redirect->type == HERE_DOC)    //5
// 			;
// 		else if (minishell->redirect->type == OUTPUT_APPEND) //6
// 			handle_append_redirect(minishell, minishell->redirect);
// 		minishell->redirect = minishell->redirect->next;

// 	}
// }

void set_redirect(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	 *tmp_token;
	t_redirect *redirect;

	minishell->heredoc_cnt = 0;
	tmp_token = parse_tree->token;
	//heredoc 갯수 체크하여 minishell구조체에 저장/redirection은 정보를 리스트에저장
	while(tmp_token)
	{
		if (tmp_token->type == INPUT || tmp_token->type == OUTPUT_OVER || \
			tmp_token->type == HERE_DOC || tmp_token->type == OUTPUT_APPEND)
		{
			redirect = redir_lstnew(tmp_token->type, tmp_token->next->value);
			if (tmp_token->type == HERE_DOC)    //5
				minishell->heredoc_cnt++;
			redir_lstadd_back(&(minishell->redirect), redirect);
			tmp_token = tmp_token->next->next;
		}
		else
		{
			tmp_token = tmp_token->next;
		}
	}
}
