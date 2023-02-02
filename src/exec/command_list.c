#include "minishell.h"
#include "exec.h"
#include "lexer.h"

void	execute_and_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	// printf("in and node\n");
	iterate_tree(minishell, parse_tree->left, pipe);
	if (minishell->exit_status == 0)
		iterate_tree(minishell, parse_tree->right, pipe);
}

void	execute_or_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	// printf("in or node\n");
	iterate_tree(minishell, parse_tree->left, pipe);
	if (minishell->exit_status != 0)
		iterate_tree(minishell, parse_tree->right, pipe);
}

void	execute_pipe_node(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipes, int fd[2])
{
	// printf("in pipe node\n");
	if (pipe(fd) == ERR)
		shell_exit(minishell, 1, "error");
	lstadd_front(&pipes, lstnew(fd));
	iterate_tree(minishell, parse_tree->left, pipes);
	iterate_tree(minishell, parse_tree->right, pipes);
}

void	handle_iteration(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	int	fd[2];
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
		execute_and_node(minishell, parse_tree, pipe);
	else if (parse_tree->type == LOGICAL_OR)
		execute_or_node(minishell, parse_tree, pipe);
}