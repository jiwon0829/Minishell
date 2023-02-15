/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:12:42 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 09:54:05 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "heredoc.h"
#include "expander.h"
#include "signals.h"

static void	heredoc_waitpid(t_minishell *minishell, t_heredoc **heredoc,
	int *status, int pid)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->exit_status = WTERMSIG(status);
	if (minishell->exit_status == 128 + SIGINT)
	{
		free(*heredoc);
		return ;
	}
	set_signal(CATCH, IGNORE);
}

void	heredoc_child(t_minishell *minishell,
		t_heredoc *heredoc, t_token *token)
{
	char	*line;

	(void)minishell;
	check_limit(minishell, heredoc, token);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, heredoc->limit, ft_strlen(line)))
		{
			free(line);
			exit(0);
		}
		if (heredoc->quote_flag == 0)
			heredoc_dollor_expander(minishell, heredoc, &line);
		write(heredoc->fd[1], line, ft_strlen(line));
		write(heredoc->fd[1], "\n", 1);
		free(line);
	}
}

void	open_heredoc(t_minishell *minishell, t_token *token)
{
	t_heredoc	*heredoc;
	int			here_pipe[2];
	int			status;

	heredoc = init_heredoc(minishell);
	if (pipe(here_pipe) == -1)
		return (err_massage(minishell, 1, "pipe_error"));
	heredoc->fd[1] = here_pipe[1];
	heredoc->pid = fork();
	if (heredoc->pid == -1)
		return (err_massage(minishell, 1, "fork_error"));
	if (heredoc->pid)
		set_signal(IGNORE, IGNORE);
	if (heredoc->pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		heredoc_child(minishell, heredoc, token);
	}
	close(here_pipe[1]);
	heredoc_waitpid(minishell, &heredoc, &status, heredoc->pid);
	heredoc->fd[0] = here_pipe[0];
	heredoc_add_back(&(minishell->heredoc), heredoc);
}

void	check_heredoc(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*tmp_token;

	tmp_token = parse_tree->token;
	while (tmp_token)
	{
		if (tmp_token->type == HERE_DOC)
		{
			open_heredoc(minishell, tmp_token);
			if (minishell->exit_status == 130)
				return ;
			tmp_token = tmp_token->next->next;
		}
		else
			tmp_token = tmp_token->next;
	}
}

void	exec_heredoc(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_parse_tree	*tmp;

	tmp = parse_tree;
	if (minishell->exit_status == 130)
		return ;
	if (tmp && tmp->type == WORD)
	{
		check_heredoc(minishell, tmp);
	}
	else
	{
		if (tmp && tmp->left)
			exec_heredoc(minishell, tmp->left);
		if (tmp && tmp->right)
			exec_heredoc(minishell, tmp->right);
	}
}
