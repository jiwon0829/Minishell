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
#include "term_signal.h"

///static void print_heredoc_list(t_heredoc *head);

void heredoc_child(t_minishell *minishell, t_heredoc *heredoc, t_token *token)
{
	char	*line;

	(void)minishell;
	heredoc->limit = token->next->value;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, heredoc->limit, ft_strlen(line)))
		{
			free(line);
			exit(0);
		}
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
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pid == 0)
		heredoc_child(minishell, heredoc, token);
	close(here_pipe[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))	//0이 아닌값 리턴하면 자식프로세스가 정상종료
		minishell->exit_status = WEXITSTATUS(status); //WIFEXITED 정상종료되면 여기서 종료코드 확인가능
	else if (WIFSIGNALED(status))	//이 매크로가 참이면 자식프로세스가 비정상종료
		minishell->exit_status = WTERMSIG(status); // WIFESIGNALED가 참일경우 종료코드 확인가능
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
			tmp_token = tmp_token->next->next;
		}
		else
			tmp_token = tmp_token->next;
	}
}

/*static void print_heredoc_list(t_heredoc *head)
{
	while (head)
	{
		printf("(%d\t%d)\n", head->fd[0], head->fd[1]);
		head = head->next;
	}
	printf("\n");
}*/

void exec_heredoc(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_parse_tree *tmp;

	tmp = parse_tree;
	if(tmp && tmp->type == WORD)
	{
		signal(SIGINT, heredoc_handler);
		check_heredoc(minishell, tmp);
		setting_signal();
	}
	else
	{
		if (tmp && tmp->left)
			exec_heredoc(minishell, tmp->left);
		if (tmp && tmp->right)
			exec_heredoc(minishell, tmp->right);
	}
	
}