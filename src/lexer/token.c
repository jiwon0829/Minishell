#include "minishell.h"
#include "unistd.h"
#include "lexer.h"

t_token	*create_token(int length, char *start, int type)
{
	t_token	*token;

	if (!length && !(type == DQUOT || type == SQUOT)) 
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->tok = start;
	char *separs[9];
	int index[9];
	init_separs(separs);
	init_index(index);
	token->tok = ft_substr(token->tok,0, length);

	token->type = type;
	printf("(%s) -> ",token->tok);
	return (token);
}

void	add_token(t_token **first, t_token *to_add)
{
	t_token	*temp;

	if (!to_add)
	{
		return ;
	}
	if (!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}