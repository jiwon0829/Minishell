#include "minishell.h"
#include "exec.h"


// t_pipe *setting_pipe(t_parse_tree *parse_tree)
// {
// 	(void)parse_tree;
// 	t_pipe *ret;
// 	// 이전 설정해놓은 리다이렉션 정보와 parsetree를 파이프 구조체에 담기
// 	return(ret);
// }


void iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	// expander(parse_tree); -> 해야함
	// redirection(parse_tree); -> handle_iteration에서했음
	// setting_pipe(parse_tree); ->따로 할거없음
	handle_iteration(minishell, parse_tree, pipe);
	// exit_value_set(minishell, minishell->exit_status); ->내부에서 되고있음
}

void executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe *pipe;
	t_redirect *redir;

	pipe = NULL;
	redir = NULL;
	minishell->redirect = redir;
	//히어독,(히어독확장)
	iterate_tree(minishell, parse_tree, pipe);

	free(pipe);
}