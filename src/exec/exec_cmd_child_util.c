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

void exec_child_logical(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe, char **envp)
{
	get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		if (parse_tree->token == NULL)
			exit (0);	
		// 파이프 라인에서 중간노드
		if((pipe->next != NULL && pipe->right_flag == 1) && parse_tree->up->type
			 == PIPE && parse_tree->up->up->type == PIPE)
			dup2(pipe->next->fd[1], STDOUT_FILENO);
		// 파이프 라인에서 제일처음노드
		else if((pipe && pipe->right_flag != 1) && parse_tree->up->type == PIPE)
		{
			close(pipe->fd[0]);
			dup2(pipe->fd[1], STDOUT_FILENO);
			close(pipe->fd[1]);
		}
		//마지막 실행 (파이프라인에서 마지막노드)
		else
			close(pipe->fd[1]);
		redir_dup(minishell);
		if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
		{
			exec_builtin(minishell, parse_tree);
			exit(minishell->exit_status);
		}
		else
			run_program(parse_tree->token->arg, envp);
}

void exec_child_scmd(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe, char **envp)
{
	(void)pipe;
		get_cmd(minishell, parse_tree->token->arg, parse_tree, envp);
		if (parse_tree->token == NULL)
			exit (0);	
		redir_dup(minishell);//redirect 반영
		if (check_builtin(minishell->cmd_tbl, parse_tree->token->value))
		{
			exec_builtin(minishell, parse_tree);
			exit(minishell->exit_status);
		}
		else
			run_program(parse_tree->token->arg, envp);
}