/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:22:58 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 18:19:46 by inosong          ###   ########.fr       */
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

void	exec_builtin(t_minishell *minishell, t_parse_tree *parse_tree)
{
	char	**cmds;

	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		redir_dup(minishell);
		cmds = make_cmd_arg(parse_tree);
		ft_execve(minishell, minishell->cmd_tbl, cmds);
		while (*cmds)
			free(*cmds++);
	}
}

void	exec_builtin_scmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
	exec_builtin(minishell, parse_tree);
	dup2(minishell->exit_fdin, STDIN_FILENO);
	dup2(minishell->exit_fdout, STDOUT_FILENO);
}

void	exec_multi_cmd(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes)
{
	pipes->pid = fork();
	setting_child();
	if (pipes->pid < 0)
		shell_err(minishell, 1, "error");
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
