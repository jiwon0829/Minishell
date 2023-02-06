#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"


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
	printf("in redir_dup\n");
	(void)minishell;
	if (redirect == NULL)
	{
		printf("redir NULL\n");
		return ;
	}
	while (redirect)
	{
		printf ("redirec while one\n");
		printf("str :%s\n",redirect->file_name);
		if (redirect->type == INPUT) //3
		{
			printf("fd< : %d\n", redirect->fd[0]);
			dup2(redirect->fd[0], STDIN_FILENO);
			close(redirect->fd[0]);
		}
		else if (redirect->type == OUTPUT_OVER)//4
		{
			printf("fd> : %d\n", redirect->fd[1]);
			dup2(redirect->fd[1], STDOUT_FILENO);
			close(redirect->fd[1]);
		}
		else if (redirect->type == HERE_DOC)    //5
		{
			printf("fd<< : %d\n", minishell->heredoc->fd[0]);
			dup2(minishell->heredoc->fd[0], STDIN_FILENO);
			close(minishell->heredoc->fd[0]);
			minishell->heredoc = minishell->heredoc->next;
		}
		else if (redirect->type == OUTPUT_APPEND) //6
		{
			printf("fd>> : %d\n", redirect->fd[1]);
			dup2(redirect->fd[1], STDOUT_FILENO);
			close(redirect->fd[1]);
		}
		redirect = redirect->next;
	}
		// dup2(redirect->fd[0], STDIN_FILENO);
	// close(redirect->fd[0]);

		// dup2(redirect->fd[1], STDOUT_FILENO);
	// close(redirect->fd[1]);

		// dup2(redirect->fd[1], STDOUT_FILENO);
	// close(redirect->fd[1]);
}

void	redir_lstadd_back(t_redirect **head, t_redirect *new)
{
	// 	new->next = *(head);
	// *(head) = new;

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


	// t_redirect **temp;

	// // printf("back type :%d\n",new->type);
	// temp = head;
	// if (temp == NULL)
	// 	(*temp) = new;
	// else
	// {
	// 	while (*(temp))
	// 		*(temp) = (*temp)->next;
	// 	*(temp) = new;
	// 	new->next = NULL;
	// 	// (*head)->next = new;
	// 	// new->next = NULL;
	// }
	// printf("back type :%d\n",(*head)->type);

	// new->next = *(head);
	// *(head) = new;
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
