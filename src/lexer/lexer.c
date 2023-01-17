#include "minishell.h"
#include "lexer.h"

int	sub_set_token_types(char **separs, int *index, t_token *temp)
{
	int	i;
			printf("set type %s,%d\n",temp->tok,temp->len);

	i = 0;
	while (separs[i])
	{
			// printf("c\n");

		if (i == 9)
		{
			perror("wrong separator");//syntax error or 임시 에러표시 에러함수따로 할지?
			return (0);
		}
		else if (temp->type == LOGICAL_AND && temp->len == 1)
		{
			perror("wrong separator");//syntax error or 임시 에러표시 에러함수따로 할지?
			return (0);
		}
		if (ft_strncmp(separs[i], temp->tok, temp->len) == 0)
		{
			temp->type = index[i];
			printf("a\n");
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
			printf("\n%s ,%d\n",(*token)->tok, temp->type);

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


// () (())  subshell 짝 맞는거 체크 할지/ sub subshell 체크할지 PRNTH_LEFT,RIGHT 만날때마다 index ++ 시켜서 짝 맞는치 체크 (아직안함)
// ex (echo a && (echo b)) && echo c
// 현재 각 위치에서 ( , ) 각각토큰화
// & && &&& &&&& 일단토큰화후 이후에 검사
void	sub_lexer(int *type, char *input_i, char **start, t_token **tokens)
{
	if (*type == SPACE && get_type(*input_i) != SPACE) 
		init_common_token(tokens, input_i, start, type);
	else if (*type == WORD && get_type(*input_i) != WORD)
		init_common_token(tokens, input_i, start, type);
	else if (*type == SEPAR_LESS && get_type(*input_i) != SEPAR_LESS)
		init_common_token(tokens, input_i, start, type);
	else if (*type == SEPAR_MORE && get_type(*input_i) != SEPAR_MORE)
		init_common_token(tokens, input_i, start, type);
	else if (*type == SEPAR_PIPE && get_type(*input_i) != SEPAR_PIPE)
		init_common_token(tokens, input_i, start, type);
	else if (*type == PRNTH_LEFT)
		init_common_token(tokens, input_i, start, type);
	else if (*type == PRNTH_RIGHT)
		init_common_token(tokens, input_i, start, type);
	else if (*type == LOGICAL_AND && get_type(*input_i) != LOGICAL_AND)
		init_common_token(tokens, input_i, start, type);
}

int	sub_lexer_quotes(int *type, char *input_i, \
					char **start, t_token **tokens)
{
	int	ret;

	ret = 0;
	if (get_type(*input_i) == DQUOT || \
					get_type(*input_i) == SQUOT)
	{
		if (!(*tokens)) // "ls" && ls 아예처음 나올때
			init_common_token(tokens, input_i, start, type);
		ret = init_quot_token(tokens, input_i, start, type);
		if (ret == -1)
		{
			free_tokens(*tokens);
			return (-1);
		}
	}
	return (ret);
}


//1. type 체크, 토큰화(word에 QUOT나오면 짝확인) 괄호도 같은방식으로할지 고민중, 
//2. 이전처럼 구조체에 문자 자체로 저장할지, 문자열+길이로 저장할지 (현재 문자열+길이) -> 추가 메모리할당 안하고 바로 쓸수있음
// ex) echo a"ab'"   'ab'bv "$ab"
//-> 토큰 : echo(word) -> a(word) -> ab'(") -> ' '(space) -> ' '(space) -> ' '(space) -> ab(') -> bv(word) -> ' '(space) -> $ab(")
// 스페이스토큰 -> 반복해서 만나면 ++시켜서 1개짜리로 or 현재처럼반복 
// t_token	*lexer(t_minishell *minishell, char *input)
t_token	*lexer(char *input)
{
	int		i;
	int		type;
	int		temp;
	char	*start;
    t_token *tokens;
	
    if (!ft_strlen(input))
		return (NULL);
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	// printf("%d\n", type);
	start = input;
	while (input[i])
	{
		sub_lexer(&type, &input[i], &start, &tokens);
		temp = sub_lexer_quotes(&type, &input[i], &start, &tokens);
		if (temp == -1)
		{
			// minishell->status = 1;
			 return (NULL); // 한줄로못쓰면 sub_lexer함수내에서 전역변수사용 (25줄초과)
		}
		i += temp + 1;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type)); //마지막토큰 NULL타입추가 or 이전처럼 \n 추가한상태로 개행타입, 현재 없음 // 길이 0 짜리 quot 생성안할지(현재 생성함) 
	if (set_token_types(&tokens) == -1)
		return (free_tokens(tokens));
	return (tokens);
}
