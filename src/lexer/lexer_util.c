#include "minishell.h"
#include "lexer.h"

void	init_separs(char **separs)
{
	separs[0] = ">";
	separs[1] = "<";
	separs[2] = ">>";
	separs[3] = "<<";
	separs[4] = "|";
	separs[5] = "(";
	separs[6] = ")";
	separs[7] = "&&";
	separs[8] = "||";
}

void	init_index(int *index)
{
	index[0] = OUTPUT_OVER;
	index[1] = INPUT;
	index[2] = OUTPUT_APPEND;
	index[3] = HERE_DOC;
	index[4] = PIPE;
	index[5] = PRNTH_LEFT;
	index[6] = PRNTH_RIGHT;
	index[7] = LOGICAL_AND;
	index[8] = LOGICAL_OR;
}


int get_type(char input)
{
    if (input == ' ' || (input >= 9 && input <= 13))
        return (BLANK);
    // if (input == '\'')
    //     return (SQUOT);
    // if (input == '\"')
	// 	return (DQUOT);
	if (input == '|')
		return (SEPAR_PIPE);
	if (input == '>')
		return (SEPAR_MORE);
	if (input == '<')
		return (SEPAR_LESS);
	if (input == '&')
		return (LOGICAL_AND);
	if (input == '(')
		return (PRNTH_LEFT);
	if (input == ')')
		return (PRNTH_RIGHT);
	return (WORD);
}

int	init_quot_token(t_token **token, char *input, char **start, int *type)
{
	int	i;

	i = 1;
	while (input[0] != input[i])
	{
		// if (input[i] == '\0')
		// {
		// 	perror("quotes are not closed");
		// 	return (-1);
		// }
		i++;
	}
	(void)token ;
	(void)start ;
	(void)type;
	return (i);
}

void    init_common_token(t_token **token, char *input, char **start, int *type)
{
	
	add_token(token, create_token((int)(input - *start), *start, *type));
    *start = input;
    *type = get_type(*input);
}
