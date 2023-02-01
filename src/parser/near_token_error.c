#include "parser.h"
#include "error_message.h"

int first_token_error(t_token *token)
{
    if (token && (token->type == LOGICAL_AND || token->type == LOGICAL_OR \
        || token->type == PIPE || token->type == PRNTH_RIGHT))
        return (snytax_error_message(token->value));
    return (1);
}

int last_token_error(t_token *token)
{
    t_token *node;

    node = token;
    while (node && node->next)
        node = node->next;
    if (node && (node->type == WORD || node->type == PRNTH_RIGHT))
        return (1);
    return (snytax_error_message(node->value));
}

