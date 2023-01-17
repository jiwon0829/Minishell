#include "minishell.h"
#include "unistd.h"
#include "lexer.h"

t_token	*create_token(int length, char *start, int type)
{
	t_token	*token;

    // 길이 0 이고 ",' 둘다 아닐때 //문자열 마지막 WORD type이고 길이는 0
    // 그런데 ex) echo__""_s f -> space "" space s 로되면 space가 1개만나와야하는데 "" 토큰때문에 space 2번될것같기도함 -> "" 만있으면 토큰화 안할지??
    // 수정할거면 조건을 if (!length) 로 수정해서 마지막 널문자랑, 내용없는 "", '' 도 토큰화 안하기
	if (!length && !(type == DQUOT || type == SQUOT)) 
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->tok = start;
	// write(1,"p\n",2);
	char *separs[9];
	int index[9];
	init_separs(separs);
	init_index(index);
	// write(1,"g\n",2);
	token->tok = ft_substr(token->tok,0, length);
	// write(1,"b\n",2);
    // printf("1. %d\n",type);

	token->type = type;
	printf("(%s) -> ",token->tok);
	// if((token->tok))
		// printf("create :%s, len :%d\n",token->tok, length);
	// write(1,"z\n",2);
	// free(token->tok);
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