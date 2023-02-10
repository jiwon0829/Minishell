#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "heredoc.h"


t_heredoc *init_heredoc(t_minishell *minishell)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)malloc(sizeof(*heredoc));
	if (!heredoc)
		err_massage(minishell, 1, "malloc error");
	heredoc->fd[0] = 0;
	heredoc->fd[1] = 0;
	heredoc->next = NULL;
	heredoc->limit = NULL;
	heredoc->pid = 0;
	return (heredoc);

}

void	heredoc_add_back(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*node;

	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	node->next = new;
}