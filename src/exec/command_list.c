/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:17:02 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 17:27:56 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "lexer.h"
#include "redirect.h"
#include "term_signal.h"
#include "test_code.h"

void	execute_and_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes, int fd[2])
{
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(&pipes, lstnew(fd));
	pipes->left_flag = 1;
	iterate_tree(minishell, parse_tree->left, pipes);
	dup2(minishell->exit_fdin, STDIN_FILENO);
	if (minishell->exit_status == 0)
	{
		pipes->right_flag = 1;
		iterate_tree(minishell, parse_tree->right, pipes);
	}
}

void	execute_or_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes, int fd[2])
{
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(&pipes, lstnew(fd));
	pipes->left_flag = 1;
	iterate_tree(minishell, parse_tree->left, pipes);
	dup2(minishell->exit_fdin, STDIN_FILENO);
	if (minishell->exit_status != 0)
	{
		printf("or right\n");
		pipes->right_flag = 1;
		iterate_tree(minishell, parse_tree->right, pipes);
	}
}

void	execute_pipe_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipes, int fd[2])
{
	minishell->pipe_cnt++;
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(&pipes, lstnew(fd));
	pipes->left_flag = 1;
	iterate_tree(minishell, parse_tree->left, pipes);
	pipes->right_flag = 1;
	iterate_tree(minishell, parse_tree->right, pipes);
}

void	handle_iteration(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe *pipe)
{
	int	fd[2];

	if (!parse_tree)
		return ;
	parse_tree->token->fd_in = 0;
	parse_tree->token->fd_out = 0;
	if (parse_tree->type == PIPE)
		execute_pipe_node(minishell, parse_tree, pipe, fd);
	else if (parse_tree->type == WORD)
	{
		if (parse_tree->token->fd_in != ERR
			&& parse_tree->token->fd_out != ERR)
			exec_cmd(minishell, parse_tree, pipe);
		else
		{
			minishell->exit_status = 1;
			exit_value_set(minishell, 1);
			return ;
		}
	}
	else if (parse_tree->type == LOGICAL_AND)
		execute_and_node(minishell, parse_tree, pipe, fd);
	else if (parse_tree->type == LOGICAL_OR)
		execute_or_node(minishell, parse_tree, pipe, fd);
}
