/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:07:53 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 13:13:34 by inosong          ###   ########.fr       */
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
#include "test_code.h"

int	redir_dup_input(t_minishell *minishell)
{
	int	ret;

	minishell->redirect->fd[0] = open(minishell->redirect->file_name, O_RDONLY);
	ret = dup2(minishell->redirect->fd[0], STDIN_FILENO);
	close(minishell->redirect->fd[0]);
	if (minishell->redirect->fd[0] == FAILURE)
	{
		if (minishell->scmd_builtin == 1 || minishell->inchild == 0)
		{
			redir_open_error_message(minishell,
				1, minishell->redirect->file_name);
			return (FAILURE);
		}
		redir_open_error_message(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == FAILURE)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
	return (1);
}

void	redir_dup_output_over(t_minishell *minishell)
{
	int	ret;

	minishell->redirect->fd[1] = open(minishell->redirect->file_name, \
		O_RDWR | O_TRUNC | O_CREAT, 0666);
	ret = dup2(minishell->redirect->fd[1], STDOUT_FILENO);
	close(minishell->redirect->fd[1]);
	if (minishell->redirect->fd[1] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}

void	redir_dup_heredoc(t_minishell *minishell)
{
	int	ret;

	ret = dup2(minishell->heredoc->fd[0], STDIN_FILENO);
	close(minishell->heredoc->fd[0]);
	minishell->heredoc = minishell->heredoc->next;
	if (minishell->redirect->fd[0] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}

void	redir_dup_output_append(t_minishell *minishell)
{
	int	ret;

	minishell->redirect->fd[1] = open(minishell->redirect->file_name, \
		O_RDWR | O_APPEND | O_CREAT, 0666);
	ret = dup2(minishell->redirect->fd[1], STDOUT_FILENO);
	close(minishell->redirect->fd[1]);
	if (minishell->redirect->fd[1] == -1)
	{
		exit_err_massage(minishell, 1, minishell->redirect->file_name);
	}
	if (ret == -1)
	{
		exit_err_massage(minishell, 1, "dup2_error");
	}
}
