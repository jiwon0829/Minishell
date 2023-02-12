#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"

static void pass_tree_token(t_minishell *minishell, t_parse_tree *parse_tree)
{
	(void)minishell;
	while(parse_tree->token)
		{
			if(parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
				parse_tree->token = parse_tree->token->next->next;
			else
				break;
		}
}

static void delete_not_word_token(t_minishell *minishell, t_parse_tree *parse_tree)
{
	(void)minishell;
	while(parse_tree->token)
	{
		if (parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
		{
			parse_tree->token->prev->next = parse_tree->token->next->next; 	
			parse_tree->token = parse_tree->token->next->next;
			// parse_tree->token->prev->next = NULL;
			// break;
		}
		else
			parse_tree->token = parse_tree->token->next;
	}
}

void set_cmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token *tmp_token;

	(void)minishell;
	// 토큰이 워드가 아니면(리다이렉션) 워드가 나올때까지 토큰리스트 이동
	if (parse_tree->token->type == WORD)
		;
	else
	{
		pass_tree_token(minishell, parse_tree);
	}
	tmp_token = parse_tree->token;
	//word토큰뒤의 리다이렉션을 제거(주소제거)
	delete_not_word_token(minishell, parse_tree);
	parse_tree->token = tmp_token;
}