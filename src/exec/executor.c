

#include "minishell.h"
#include "exec.h"
#include "heredoc.h"
#include "redirect.h"
#include "signals.h"
#include "expander.h"

void	iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipe)
{
	t_heredoc	*tmp;
	int			i;

	i = 0;
	expander(minishell, parse_tree);
	handle_iteration(minishell, parse_tree, pipe);
	if (parse_tree->type == 0)
	{
		while (i < minishell->heredoc_cnt)
		{
			if (minishell->heredoc)
			{
				tmp = minishell->heredoc->next;
				free(minishell->heredoc->limit);
				free(minishell->heredoc);
				minishell->heredoc = tmp;
			}
			i++;
		}
	}
}

void	executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe			*pipe;

	pipe = NULL;
	minishell->heredoc = NULL;
	minishell->exit_fdin = dup(STDIN_FILENO);
	minishell->exit_fdout = dup(STDOUT_FILENO);
	exec_heredoc(minishell, parse_tree);
	if (minishell->exit_status == 128 + SIGINT)
	{
		minishell->exit_status = 1;
		return ;
	}
	iterate_tree(minishell, parse_tree, &pipe);
}
