/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:24:05 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 15:53:17 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;
	i = 0;\
	expander(minishell, parse_tree);

	handle_iteration(minishell, parse_tree, pipe);
	if (parse_tree->type == 0)
	{
		while (i < minishell->heredoc_cnt)
		{
			if (minishell->heredoc)
			{
				printf("in free heredoc\n");
				tmp = minishell->heredoc->next;
				free(minishell->heredoc->limit);
				free(minishell->heredoc);
				minishell->heredoc = tmp;
				// minishell->heredoc = minishell->heredoc->next;
			}
			i++;
		}
	}

}

static void ffree_pipe(t_pipe *pipe)
{
	t_pipe *tmp;
	return ;
	printf("in ffree pipe\n");

	if ((pipe))
	{
		printf("prev ok\n");
		while((pipe))
		{
			tmp = pipe->next;
			// (pipe) = (pipe)->next;
			printf("free)pipe_while on\n");
			free(pipe);
			pipe = tmp;
			// break;
			// *pipe = (*pipe)->next;
			// printf("free)pipe_while on\n");

		}
		// (pipe) = NULL;
	}
}
void	executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe			*pipe;
	// t_redirect		*redir;
	// t_pipe			*tmp;

	// pipe = malloc(sizeof(t_pipe));
	// *pipe = NULL;
	pipe = NULL;
	// redir = NULL;
	minishell->heredoc = NULL;
	minishell->exit_fdin = dup(STDIN_FILENO);
	minishell->exit_fdout = dup(STDOUT_FILENO);
	// minishell->redirect = redir;
	exec_heredoc(minishell, parse_tree);
	if (minishell->exit_status == 128 + SIGINT)
	{
		minishell->exit_status = 1;
		return ;
	}
	// tmp = pipe;

	iterate_tree(minishell, parse_tree, &pipe);
	// printf("!!>>>>>>>pipe_fd%d<<<<\n",pipe->fd[1]);

	// pipe = tmp;
	// system("leaks minishell");

	ffree_pipe(pipe);
	//system("leaks minishell");
	// free(pipe);
}
