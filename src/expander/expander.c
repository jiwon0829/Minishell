#include "minishell.h"
#include "expander.h"
#include "envp.h"

void	expander(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*token;

	token = parse_tree->token;
	while (token)
	{
		if (!envp_expand(token) || !quote_delete(token) || !wildcard(token))
		{
			minishell->exit_status = 1;
			return ;
		}
		token = token->next;
	}
}
