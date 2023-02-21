/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:20:40 by inosong           #+#    #+#             */
/*   Updated: 2023/02/21 16:59:46 by jiwonhan         ###   ########seoul.kr  */
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
#include "signals.h"


int	exec_child_logical(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipe, char **envp)
{
	get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
	if (parse_tree->token == NULL)
		exit (0);
	if (((*pipe)->next != NULL && (*pipe)->right_flag == 1)
		&& parse_tree->up->type
		== PIPE && parse_tree->up->up->type == PIPE)
		dup2((*pipe)->next->fd[1], STDOUT_FILENO);
	else if ((pipe && (*pipe)->right_flag != 1) && parse_tree->up->type == PIPE)
	{
		close((*pipe)->fd[0]);
		dup2((*pipe)->fd[1], STDOUT_FILENO);
		close((*pipe)->fd[1]);
	}
	else
		close((*pipe)->fd[1]);
	if (redir_dup(minishell) == FAILURE)
		return (1);
	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		exec_builtin(minishell, parse_tree);
		exit(minishell->exit_status);
	}
	else
		run_program(parse_tree->token->arg, envp);
	return (127);
}

int	exec_child_scmd(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipe, char **envp)
{
	(void)pipe;
	if (parse_tree->token == NULL)
		exit(0);
	get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
	if (redir_dup(minishell) == FAILURE)
		return (1);
	if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
	{
		exec_builtin(minishell, parse_tree);
		exit(minishell->exit_status);
	}
	else
		run_program(parse_tree->token->arg, envp);
	return (127);
}
