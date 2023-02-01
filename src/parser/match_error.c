#include "parser.h"
#include "error_message.h"

int parenthesis_match_error(t_token *token)
{
    t_token *node;
    int     parenthesis = 0;

    node = token;
    while (node)
    {
        if (!parenthesis && node->type == PRNTH_RIGHT)
            break ;
        if (node->type == PRNTH_LEFT || node->type == PRNTH_RIGHT)
            parenthesis += node->type;
        if (parenthesis < 0)
            break ;
    }
    if (parenthesis == 0)
        return (1);
    return (snytax_error_message(")"));
}
