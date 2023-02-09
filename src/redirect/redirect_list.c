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


#include <errno.h>

static int	re_lstsize(t_redirect *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

static t_redirect	*re_lstlast(t_redirect *lst)
{
	if (re_lstsize(lst) == 0)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}


void redir_dup(t_minishell *minishell, t_redirect *redirect)
{
	(void)minishell;
	while (redirect)
	{
		if (redirect->type == INPUT) //3
		{
			int ret;
			redirect->fd[0] = open(redirect->file_name, O_RDONLY);
			ret = dup2(redirect->fd[0], STDIN_FILENO);
			//이런식으로 dup2실패하는지 체크해서 에러처리 하면좋을듯 리다이렉션전체
			if (ret == -1)
			{
				perror("dup2");
				printf("errno : %d open failed : %s\n",errno, strerror(errno));

			}
			close(redirect->fd[0]);

		}
		else if (redirect->type == OUTPUT_OVER)//4
		{
			redirect->fd[1] = open(redirect->file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
			dup2(redirect->fd[1], STDOUT_FILENO);close(redirect->fd[1]);
		}
		else if (redirect->type == HERE_DOC)    //5
		{
			dup2(minishell->heredoc->fd[0], STDIN_FILENO);
			close(minishell->heredoc->fd[0]);
			minishell->heredoc = minishell->heredoc->next;
		}
		else if (redirect->type == OUTPUT_APPEND) //6
		{
			redirect->fd[1] = open(redirect->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
			dup2(redirect->fd[1], STDOUT_FILENO);
			close(redirect->fd[1]);
		}
		redirect = redirect->next;
	}

}

void	redir_lstadd_back(t_redirect **head, t_redirect *new)
{
	t_redirect	*end_list;

	if (!new || !head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	end_list = re_lstlast(*head);
	end_list->next = new;
}

t_redirect	*redir_lstnew(int type, char *value)
{
	t_redirect	*lst;

	lst = (t_redirect *)malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->type = type;
	lst->file_name = value;
	lst->fd[0] = 0;
	lst->fd[1] = 0;
	lst->next = NULL;
	return (lst);
}
