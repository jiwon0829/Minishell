#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"

void remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
{
	
}

void expender(t_minishell *minishell, t_parse_tree *parse_tree)
{
	char	*new_str;
	int		i;
	// is_wildcard();//여기서 와일드카드처리
	while (parse_tree->token)
	{
		while (parse_tree->token->value[i])
		{
			if (parse_tree->token->value[i] == '"')
				remove_squotes(minishell, parse_tree, &i);
			else if (parse_tree->token->value[i] == "'")
				remove_dquotes(minishell, parse_tree, &i);
			else if (parse_tree->token->value[i] == "$")
				remove_dollor(minishell, parse_tree, &i);
			i += i;
		}
		parse_tree->token = parse_tree->token->next;
	}
}