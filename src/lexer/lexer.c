#include "minishell.h"
#include "lexer.h"

//토큰체크용 함수
static void lexer_check(t_token *token)
{
    t_token *test;
    test = token;
	while(test)
	{
		printf("(%s)",test->value);
        if (test->type == 2)
    		printf("type:PIPE -> ");
        else if (test->type == 3)
            printf("type:INPUT -> ");
        else if (test->type == 4)
    		printf("type:OUTPUT_OVER -> ");        
        else if (test->type == 5)
    		printf("type:HERE_DOC -> ");
        else if (test->type == 6)
            printf("type:OUTPUT_APPEND -> ");
        else if (test->type == 10)
    		printf("type:PRNTH_LEFT -> ");
        else if (test->type == 11)
    		printf("type:PRNTH_LEFT ");    
        else if (test->type == 12)
            printf("type:LOGIC_AND -> ");
        else if (test->type == 13)
    		printf("type:LOGIC_OR -> ");
		else
			printf("type:WORD ->");
		test = test->next;
	}
    printf("\n");
}

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
    //렉서 타입체크함수
	lexer_check(token);
    return (token);
}