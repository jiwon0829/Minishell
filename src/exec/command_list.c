/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:17:02 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 15:55:36 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "lexer.h"
#include "redirect.h"
#include "signals.h"
#include "test_code.h"

void	free_n_move_pipe(t_minishell *minishell, t_pipe **pipes)
{
	(void)minishell;
	if ((*pipes) && (*pipes)->right_flag == 1)
	{
		if ((*pipes)->type == PIPE)
		{
			t_pipe *tmp;
			tmp = (*pipes)->next;
			free(*pipes);
			(*pipes) = tmp;
		}
		else if((*pipes) && (*pipes)->type == LOGICAL)
		{
			t_pipe *tmp;
			tmp = (*pipes)->next;
			free(*pipes);
			(*pipes) = tmp;
		}
	}
}

void	execute_and_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipes, int fd[2])
{
	fd[0] = 0;
	fd[1] = 4;
	lstadd_front(pipes, lstnew(fd));
	(*pipes)->type = LOGICAL;
	(*pipes)->left_flag = 1;
	iterate_tree(minishell, parse_tree->left, pipes);
	dup2(minishell->exit_fdin, STDIN_FILENO);
	free_n_move_pipe(minishell, pipes);
	if (minishell->exit_status == 0)
	{
		(*pipes)->right_flag = 1;
		iterate_tree(minishell, parse_tree->right, pipes);
	}
	free_n_move_pipe(minishell, pipes);
}

void	execute_or_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipes, int fd[2])
{
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(pipes, lstnew(fd));
	(*pipes)->type = LOGICAL;
	(*pipes)->left_flag = 1;
	iterate_tree(minishell, parse_tree->left, pipes);
	dup2(minishell->exit_fdin, STDIN_FILENO);
	free_n_move_pipe(minishell, pipes);
	(*pipes)->right_flag = 1;
	if (minishell->exit_status != 0)
	{
		iterate_tree(minishell, parse_tree->right, pipes);
	}
	free_n_move_pipe(minishell, pipes);
}

void	execute_pipe_node(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipes, int fd[2])
{
	minishell->pipe_cnt++;
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(pipes, lstnew(fd));
	(*pipes)->left_flag = 1;
	(*pipes)->type = PIPE;
	iterate_tree(minishell, parse_tree->left, pipes);
	free_n_move_pipe(minishell, pipes);
	(*pipes)->right_flag = 1;
	iterate_tree(minishell, parse_tree->right, pipes);
	free_n_move_pipe(minishell, pipes);

}

void	handle_iteration(t_minishell *minishell, t_parse_tree *parse_tree,
	t_pipe **pipe)
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
	{
		execute_and_node(minishell, parse_tree, pipe, fd);
	}
	else if (parse_tree->type == LOGICAL_OR)
		execute_or_node(minishell, parse_tree, pipe, fd);
	
}
