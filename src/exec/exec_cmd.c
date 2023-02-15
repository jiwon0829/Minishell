/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:26:05 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 09:32:25 by inosong          ###   ########.fr       */
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

static void	wait_pid(t_minishell *minishell, t_pipe *pipe)
{
	int	status;
	int	tmp;
	int	i;

	i = 0;
	waitpid(pipe->pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->exit_status = WTERMSIG(status);
	while (i < minishell->pipe_cnt)
	{
		wait(&tmp);
		i++;
	}
	minishell->pipe_cnt = 0;
	dup2(minishell->exit_fdin, STDIN_FILENO);
}

void	run_program(t_arg *arg, char **envp)
{
	execve(arg->cmd, arg->cmd_arg, envp);
}

void	child_process(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipe)
{
	t_arg	arg;
	char	**envp;

	minishell->exit_status = 0;
	envp = envp_to_dptr(minishell->envp);
	parse_tree->token->arg = &arg;
	if (parse_tree->up != NULL)
	{
		exec_child_logical(minishell, parse_tree, pipe, envp);
	}
	else
	{
		exec_child_scmd(minishell, parse_tree, pipe, envp);
	}
	minishell->exit_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse_tree->token->value, 2);
	shell_exit(minishell, 127, ": command not found");
}

void	parent_process(t_minishell *minishell, t_parse_tree *parse_tree,
		t_pipe *pipe)
{
	if (parse_tree->up && parse_tree->up->up
		&& parse_tree->up->up->type == PIPE && pipe->right_flag == 1)
	{
		dup2(pipe->next->fd[0], STDIN_FILENO);
		close(pipe->next->fd[1]);
		close(pipe->next->fd[0]);
	}
	else if ((parse_tree->up && parse_tree->up->type != PIPE)
		|| (pipe->right_flag == 1 && (((parse_tree->up && parse_tree->up->\
			type == PIPE) && (!(parse_tree->up->up))) || ((parse_tree->up) \
			&& (parse_tree->up->up && parse_tree->up->up->type != PIPE)))))
	{
		wait_pid(minishell, pipe);
	}
	else
	{
		close(pipe->fd[1]);
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	}
	minishell->redirect = NULL;
}

void	exec_cmd(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes)
{
	set_redirect(minishell, parse_tree);
	set_cmd(minishell, parse_tree);
	if (parse_tree->token == NULL)
		return ;
	if (((parse_tree->up == NULL
				&& check_builtin(minishell->cmd_tbl, parse_tree->token->value)))
		|| ((pipes && parse_tree->up->type != PIPE)
			&& check_builtin(minishell->cmd_tbl, parse_tree->token->value)))
		exec_builtin_scmd(minishell, parse_tree);
	else if (pipes)
		exec_multi_cmd(minishell, parse_tree, pipes);
	else
		exec_scmd(minishell, parse_tree, pipes);
	if (pipes && pipes->right_flag == 1)
	{
		pipes = pipes->next;
	}
}
