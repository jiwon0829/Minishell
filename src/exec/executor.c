#include "minishell.h"
#include "exec.h"


t_pipe *setting_pipe(t_parse_tree *parse_tree)
{
	t_pipe *ret;
	// 이전 설정해놓은 리다이렉션 정보와 parsetree를 파이프 구조체에 담기
	return(ret);
}


void iterate_tree(t_minishell *minishell, t_parse_tree *parse_tree, t_pipe *pipe)
{
	// redirection(parse_tree);
	// expander(parse_tree);
	// setting_pipe(parse_tree);
	handle_iteration(minishell, parse_tree, pipe);
	exit_value_set(minishell->exit_status);
}

void executor(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_pipe *pipe;

	//히어독,
	iterate_tree(minishell, parse_tree, pipe);

	free(pipe);
}