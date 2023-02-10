#include "minishell.h"
#include "exec.h"
#include "heredoc.h"
#include "redirect.h"

void iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	int	i;

	i = 0;
	// expander(parse_tree); -> 해야함
	handle_iteration(minishell, parse_tree, pipe);
	
	//사용한 heredoc 리스트이동
	if (parse_tree->type == 0)
	{
		while (i < minishell->heredoc_cnt)
		{
				if (minishell->heredoc)
					minishell->heredoc = minishell->heredoc->next;
			i++;
		}
	}
}

void executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe			*pipe;
	t_redirect		*redir;

	pipe = NULL;
	redir = NULL;
	minishell->heredoc = NULL;
	minishell->exit_fdin = dup(STDIN_FILENO);
	minishell->exit_fdout = dup(STDOUT_FILENO);
	minishell->redirect = redir;
	exec_heredoc(minishell, parse_tree);
	iterate_tree(minishell, parse_tree, pipe);
	free(pipe);
}