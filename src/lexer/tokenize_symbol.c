#include "minishell.h"
#include "lexer.h"

int tokenize_and_pipe(int *type, char *input_i, char **start, t_token **tokens)
{
    int temp;

    temp = 0;
    if (*type == SEPAR_PIPE)
	{
		if (get_type(input_i[1]) == SEPAR_PIPE)
		{
            init_common_token(tokens, &input_i[2], start, type);
            temp = 1;
        }
        else
			init_common_token(tokens, &input_i[1], start, type);
	}
    else if (*type == LOGICAL_AND)
    {
		if (get_type(input_i[1]) == LOGICAL_AND)
		{
            init_common_token(tokens, &input_i[2], start, type);
            temp = 1;
        }
        else
			init_common_token(tokens, &input_i[1], start, type);
	}
    else if (get_type(*input_i) == BLANK ) 
	{
		*start = &input_i[1];
	    *type = get_type(input_i[1]);
	}
    return (temp);
}

int tokenize_less_more(int *type, char *input_i, char **start, t_token **tokens)
{
    int temp;

    temp = 0;
    if (*type == SEPAR_LESS)
	{
		if (get_type(input_i[1]) == SEPAR_LESS)
		{
            init_common_token(tokens, &input_i[2], start, type);
            temp = 1;
        }
        else
			init_common_token(tokens, &input_i[1], start, type);
	}
    else if (*type == SEPAR_MORE)
    {
		if (get_type(input_i[1]) == SEPAR_MORE)
		{
            init_common_token(tokens, &input_i[2], start, type);
            temp = 1;
        }
        else
			init_common_token(tokens, &input_i[1], start, type);
	}
    else if (get_type(*input_i) == BLANK ) 
	{
		*start = &input_i[1];
	    *type = get_type(input_i[1]);
	}
    return (temp);
}

void tokenize_space(int *type, char *input_i, char **start)
{
    if (get_type(*input_i) == BLANK ) 
	{
		*start = &input_i[1];
	    *type = get_type(input_i[1]);
	}
}


int	tokenize_special(int *type, char *input_i, char **start, t_token **tokens)
{
    int temp;

    temp = 0;
    if (*type == SEPAR_LESS || *type == SEPAR_MORE)
        temp += tokenize_less_more(type, input_i, start, tokens);
    else if (*type == LOGICAL_AND || *type == SEPAR_PIPE)
        temp += tokenize_and_pipe(type, input_i, start, tokens);
    else if (*type == BLANK)
        tokenize_space(type, input_i, start);
    return (temp);
}