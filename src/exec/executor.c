#include "minishell.h"
#include "exec.h"
#include "heredoc.h"
#include "redirect.h"


// t_pipe *setting_pipe(t_parse_tree *parse_tree)
// {
// 	(void)parse_tree;
// 	t_pipe *ret;
// 	// 이전 설정해놓은 리다이렉션 정보와 parsetree를 파이프 구조체에 담기
// 	return(ret);
// }


void iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	int	i;

	i = 0;
	// expander(parse_tree); -> 해야함
	// redirection(parse_tree); -> handle_iteration에서했음
	// setting_pipe(parse_tree); ->따로 할거없음
	handle_iteration(minishell, parse_tree, pipe);
	// exit_value_set(minishell, minishell->exit_status); ->내부에서 되고있음

	//자식프로세스에서 사용한 heredoc 이동시켜서 최신화
		// printf("2finish!@!@!@!@!@!@!@\n");

	// while (parse_tree->token && parse_tree->token->prev)
	// 	parse_tree->token=parse_tree->token->prev;
	if (parse_tree->type == 0)
	{
		printf("heredoc_cnt : %d \n\n\n",minishell->heredoc_cnt);
		while (i < minishell->heredoc_cnt)
		{
			// if (parse_tree->token->type == HERE_DOC)
			// {
				if (minishell->heredoc)
					minishell->heredoc = minishell->heredoc->next;
				printf("heredoc passing \n");
			// }
			// parse_tree->token = parse_tree->token->next;
			i++;
		}
		if (minishell->heredoc)
			printf("heredoc 재배치! fd[0] = %d \n", minishell->heredoc->fd[0]);
	}
}

void executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe			*pipe;
	t_redirect		*redir;

	// minishell->exit_status = 10;
	pipe = NULL;
	redir = NULL;
	minishell->redirect = redir;

	
	// int stt[2];
	// minishell->std_fdin = 0;
	minishell->exit_fdin = dup(STDIN_FILENO);
	minishell->exit_fdout = dup(STDOUT_FILENO);
	// minishell->redirect->fd[0] = stt[0];
	// minishell->stdfd[1] = stt[1];


	//히어독,(히어독확장)
	// minishell->redirect = NULL;

	minishell->heredoc = NULL;
	//minishell->heredoc = init_heredoc(minishell);
	// printf("parse %s\n",parse_tree->left->token->value);
	// exit(0);
	exec_heredoc(minishell, parse_tree);
	// set_redirect(minishell, parse_tree);
	// if (minishell->redirect)
	// 	printf("fd : %d\n",minishell->redirect->fd[0]);

	// printf("after set_redir\n");
	// if (minishell->redirect)
	// 	printf("redir str:%s\n",minishell->redirect->file_name);
	iterate_tree(minishell, parse_tree, pipe);

	printf("finish!@!@!@!@!@!@!@\n");
	free(pipe);
}