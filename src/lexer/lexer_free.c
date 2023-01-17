#include "../../include/minishell.h"

t_token *free_tokens(t_token *token)
{
    t_token *temp;

    if (!token)
        return (NULL);
    temp = token;
    while (token)
    {
        token = token->next;
        free(temp);
        temp = token;
    }
    return (NULL);
}
