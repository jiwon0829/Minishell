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

///static void print_heredoc_list(t_heredoc *head);

void check_limit(t_minishell *minishell, t_heredoc *heredoc, t_token *token)
{
	// printf("here lim before:%s\n",token->next->value);
	heredoc->limit = heredoc_expander(minishell, heredoc, token->next->value);
	// printf("here lim after:%s\n",heredoc->limit);
}

void heredoc_child(t_minishell *minishell, t_heredoc *heredoc, t_token *token)
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

void open_heredoc(t_minishell *minishell, t_token *token)
{
	t_heredoc	*heredoc;
	int			here_pipe[2];
	int			status;
	int			pid;

	// heredoc = NULL;
	heredoc = init_heredoc(minishell);
	if (pipe(here_pipe) == -1)
		return (err_massage(minishell, 1, "pipe_error"));//메세지수정
	heredoc->fd[1] = here_pipe[1];
	pid = fork();
	if (pid == -1)
		return (err_massage(minishell, 1, "fork_error"));//메세지수정
	if (pid)
		set_signal(IGNORE, IGNORE);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		heredoc_child(minishell, heredoc, token);
	}
	close(here_pipe[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
		minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
	else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
		minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능
	if (minishell->exit_status == 128 + SIGINT)
	{
		//minishell->exit_status = 1;
		free(heredoc);
		return ;
	}
	set_signal(CATCH, IGNORE);
	heredoc->fd[0] = here_pipe[0];
	heredoc_add_back(&(minishell->heredoc), heredoc);
}

void check_heredoc(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token *tmp_token;

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

void exec_heredoc(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_parse_tree *tmp;

	tmp = parse_tree;
	if (minishell->exit_status == 130)
		return ;
	if(tmp && tmp->type == WORD)
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