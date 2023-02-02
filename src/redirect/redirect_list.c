#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"


void	redir_lstadd_back(t_redirect **head, t_redirect *new)
{
	(*head)->next = new;
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
	lst->next = NULL;
	return (lst);
}