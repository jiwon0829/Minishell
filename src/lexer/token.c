#include "minishell.h"
#include "unistd.h"
#include "lexer.h"

t_token	*create_token(int length, char *start, int type)
{
	t_token	*token;

	if (!length && !(type == DQUOT || type == SQUOT)) 
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);//널가드추가
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->value = ft_substr(start, 0, length);

	token->type = type;
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