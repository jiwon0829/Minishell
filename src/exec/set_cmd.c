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
	// t_token *tmp;
	// int		redir_flag;
	t_token *tmp_token;

	printf ("\n----in set_cmd----\n");
	(void)minishell;
	// redir_flag = 0;
	if (parse_tree->token->type == WORD)
		;
	else
	{
		while(parse_tree->token )
		{
			printf ("check token, move next\n");

			if(parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
				parse_tree->token = parse_tree->token->next->next;
			else
				break;
			// redir_flag = 1;
		}
	}
	tmp_token = parse_tree->token;
	// {
	// 	while(parse_tree->token)
	// 	{
	// 		if (parse_tree->token->type == WORD && !check_redirect(parse_tree->token->prev))
	// 		{
	// 			break;
	// 		}
	// 		parse_tree->token = parse_tree->token->next;
	// 	}
	// }
	// printf ("in set_cmd2\n");

	while(parse_tree->token)
	{
		// if (parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
		// {
		// 	parse_tree->token = parse_tree->token->next->next;
		// 	redir_flag = 1;
		// }
		// else 
		if (parse_tree->token->type >= INPUT && parse_tree->token->type <= OUTPUT_APPEND)
		{
			// printf("while trr\n");
			parse_tree->token->prev->next = NULL;
			printf("del set value next token value: %s\n",parse_tree->token->prev->value);
			break;
		}
		else
			parse_tree->token = parse_tree->token->next;
	}
	// printf ("in set_cmd3\n");
	parse_tree->token = tmp_token;
	if (parse_tree->token)
		printf(" double check cur token value: %s\n",parse_tree->token->value);
	printf ("\n----finish set_cmd----\n");

	// while(parse_tree->token && parse_tree->token->prev)
	// 	parse_tree->token = parse_tree->token->prev;

	//이거 왜 안됨?
	// tmp = parse_tree->token;
	// while(tmp)
	// {
	// 	if (tmp->type >= INPUT && tmp->type <= OUTPUT_APPEND)
	// 	{
	// 		tmp = tmp->next->next;
	// 		redir_flag = 1;
	// 	}
	// 	else if (tmp->type >= INPUT && tmp->type <= OUTPUT_APPEND && redir_flag == 1)
	// 	{
	// 		tmp->prev->next = NULL;
	// 		break;
	// 	}
	// 	else
	// 		tmp = tmp->next;
	// }
}