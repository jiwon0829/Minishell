#include "minishell.h"
#include "lexer.h"

int check_quot(char input)
{
    // if (input == ' ' || (input >= 9 && input <= 13))
    //     return (BLANK);
    if (input == '\'')
        return (SQUOT);
    else if (input == '\"')
        return (DQUOT);
    return (0);
}