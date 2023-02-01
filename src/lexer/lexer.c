#include "minishell.h"
#include "lexer.h"
#include "test_code.h"

int	sub_set_token_types(char **separs, int *index, t_token *temp)
{
	int	i;

	i = 0;
	while (separs[i])
	{
		if (ft_strncmp(separs[i], temp->value, temp->len) == 0)
		{
			temp->type = index[i];
			break ;
		}
		i++;
	}
	return (1);
}

int	set_token_types(t_token **token)
{
	t_token			*temp;
	char			*separs[9];
	int				index[9];

	init_separs(separs);
	init_index(index);
	temp = *token;
	while (temp)
	{
		if (temp->type == PRNTH_RIGHT || temp->type == SEPAR_MORE || \
				temp->type == SEPAR_PIPE || temp->type == LOGICAL_AND || \
						temp->type == PRNTH_LEFT || temp->type == SEPAR_LESS)
			if (!sub_set_token_types(separs, index, temp))
				return (-1);
		temp = temp->next;
	}	
	return (1);
}

t_token *lexer(t_token *token)
{
	if (set_token_types(&token) == -1)
        return (free_tokens(token));
	//print_lexer_token(token);	//TODO
    return (token);
}