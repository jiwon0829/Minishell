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
	printf("----in redir_dup----\n");
		print_redir_list(minishell->redirect);

	(void)minishell;
	if (redirect == NULL)
	{
		printf("redir NULL\n");
		return ;
	}
	while (redirect)
	{
		printf ("\nredirec dup2 while 1\n");
		printf("str :%s\n",redirect->file_name);
		if (redirect->type == INPUT) //3
		{
			printf("fd< : %d\n", redirect->fd[0]);
			// ret =dup2(minishell->exit_fdin, STDIN_FILENO);

			int ret;
			ret = dup2(redirect->fd[0], STDIN_FILENO);
			if (ret == -1)
			{
				perror("dup2");
				printf("errno : %d open failed : %s\n",errno, strerror(errno));

			}
			printf("!after dup2 fd[ret]: %d ,dup2 fd[0]: %d \n",ret,redirect->fd[0]);
			printf("redir str : %s\n",redirect->file_name);
			close(redirect->fd[0]);
			// printf("close -> fd< : %d\n", redirect->fd[0]);
			
			// printf("close -> fd< :???\n");

			printf("close -> fd< : %d\n", redirect->fd[0]);

			// printf("test after dup2 msg fd : %d\n", STDIN_FILENO);
			// write(STDOUT_FILENO, "hi", 2);

		}
		else if (redirect->type == OUTPUT_OVER)//4
		{
			printf("fd> : %d\n", redirect->fd[1]);
			int ret;
			// dup2(minishell->exit_fdin, STDIN_FILENO);

			ret = dup2(redirect->fd[1], STDOUT_FILENO);
			printf("!?after dup2 fd[ret]: %d ,dup2 fd[0]: %d ",ret,redirect->fd[1]);
			close(redirect->fd[1]);
			// printf("test after dup2 msg fd : %d\n", STDIN_FILENO);
		}
		else if (redirect->type == HERE_DOC)    //5
		{
			printf("fd<< : %d\n", minishell->heredoc->fd[0]);
			int ret;
			ret = dup2(minishell->heredoc->fd[0], STDIN_FILENO);
			printf("!?after dup2(here) fd[ret]: %d ,dup2 fd[0]: %d ",ret,redirect->fd[1]);

			close(minishell->heredoc->fd[0]);
			minishell->heredoc = minishell->heredoc->next;
		}
		else if (redirect->type == OUTPUT_APPEND) //6
		{
			printf("fd>> : %d\n", redirect->fd[1]);
			int ret;
			ret = dup2(redirect->fd[1], STDOUT_FILENO);
			printf("!?after_append dup2 fd[ret]: %d ,dup2 fd[0]: %d ",ret,redirect->fd[1]);
			
			
			// dup2(redirect->fd[1], STDOUT_FILENO);
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
	printf("\n----finish redir_dup----\n");

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
