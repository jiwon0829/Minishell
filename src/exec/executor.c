/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:24:05 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 17:41:15 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "heredoc.h"
#include "redirect.h"
#include "signals.h"
#include "expander.h"

void	iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipe)
{
	int	i;

	i = 0;
	expander(minishell, parse_tree);
	// system("leaks minishell");

	handle_iteration(minishell, parse_tree, pipe);
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

void	executor(t_minishell *minishell, t_parse_tree *parse_tree)
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
	if (minishell->exit_status == 128 + SIGINT)
	{
		minishell->exit_status = 1;
		return ;
	}
	// system("leaks minishell");

	// system("leaks minishell");
	iterate_tree(minishell, parse_tree, pipe);
	// free(pipe);
	
	system("leaks minishell");
	while (pipe)
	{
		
		free(pipe);
		pipe = pipe->prev;
	}
}
