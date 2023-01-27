#include "parser.h"

t_token *get_head_token(t_token *token)
{
    while (token && token->prev)
        token = token->prev;
    return (token);
}

t_token *get_tail_token(t_token *token)
{
    while (token && token->next)
        token = token->next;
    return (token);
}
