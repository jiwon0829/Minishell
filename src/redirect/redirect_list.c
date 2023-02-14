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

// #include <errno.h>

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


void redir_dup(t_minishell *minishell)
{
	while (minishell->redirect)
	{
		if (minishell->redirect->type == INPUT) //3
			redir_dup_input(minishell);
		else if (minishell->redirect->type == OUTPUT_OVER)//4
			redir_dup_output_over(minishell);
		else if (minishell->redirect->type == HERE_DOC)    //5
			redir_dup_heredoc(minishell);
		else if (minishell->redirect->type == OUTPUT_APPEND) //6
			redir_dup_output_append(minishell);
		minishell->redirect = minishell->redirect->next;
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
