/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:22:58 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 09:39:02 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"
#include "term_signal.h"
#include "test_code.h"

int	exec_builtin(t_minishell *minishell, t_parse_tree *parse_tree)
{
	char	**cmds;

	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		if (redir_dup(minishell) == -1)
			return (-1);
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		while (*cmds)
			free(*cmds++);
	}
	return (1);
}

int	exec_builtin_scmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
	minishell->scmd_builtin = 1;
	if (exec_builtin(minishell, parse_tree) == -1)
	{
		minishell->scmd_builtin = 0;
		return (-1);
	}
	dup2(minishell->exit_fdin, STDIN_FILENO);
	dup2(minishell->exit_fdout, STDOUT_FILENO);
	minishell->scmd_builtin = 0;
	return (1);
}

void	exec_multi_cmd(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes)
{
	pipes->pid = fork();
	setting_child();
	if (pipes->pid < 0)
		exit_err_massage(minishell, 1, "fork_error");
	if (pipes->pid == 0)
	{
		child_process(minishell, parse_tree, pipes);
	}
	else
		parent_process(minishell, parse_tree, pipes);
	setting_signal();
}

void	exec_scmd(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes)
{
	int	status;
	int	fd[2];

	pipe(fd);
	pipes = lstnew(fd);
	pipes->pid = fork();
	setting_child();
	if (pipes->pid < 0)
		shell_err(minishell, 1, "error");
	if (pipes->pid == 0)
	{
		child_process(minishell, parse_tree, pipes);
	}
	else
	{
		waitpid(pipes->pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->exit_status = WTERMSIG(status);
	}
	setting_signal();
}
