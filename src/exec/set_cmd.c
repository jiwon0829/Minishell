#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"

// static int check_redirect(t_token *token)
// {
// 	if (token->type == INPUT)
// 		return (1);
// 	else if (token->type == OUTPUT_APPEND)
// 		return (1);
// 	else if (token->type == OUTPUT_OVER)
// 		return (1);
// 	else if (token->type == HERE_DOC)
// 		return (1);
// 	return (0);
// }

void set_cmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token *tmp_token;

	(void)minishell;
	// 토큰이 워드가 아니면 워드가 나올때까지 토큰리스트 이동
	if (parse_tree->token->type == WORD)
		;
	else
	{
		while(parse_tree->token)
		{
			if(parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
				parse_tree->token = parse_tree->token->next->next;
			else
				break;
		}
	}
	tmp_token = parse_tree->token;
	//word토큰뒤의 리다이렉션을 제거(주소제거)
	while(parse_tree->token)
	{
		if (parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
		{
			parse_tree->token->prev->next = NULL;
			break;
		}
		else
			parse_tree->token = parse_tree->token->next;
	}
	parse_tree->token = tmp_token;
}