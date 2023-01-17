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
    if (input == ' ' || (input >= 9 && input <= 13)) //  수평탭, 줄바꿈, 수직탭, 페이지넘김, 맨앞커서이동, 
        return (SPACE);
    if (input == '\'')
        return (SQUOT);
    if (input == '\"')
		return (DQUOT);
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
// quot  짝안맞으면 종료, 짝맞으면 내용 토큰화, 다음 타입지정
int	init_quot_token(t_token **token, char *input, char **start, int *type)
{
	int	i;

	i = 1;
	while (input[0] != input[i])
	{
		if (input[i] == '\0')
		{
			perror("quotes are not closed");
			return (-1);// -1 리턴하면 status = 1로 불러온함수에서 변경 or 전역변수사용해서  에러 지점에서 수정하기
		}
		i++;
	}
	if (i == 1)
		add_token(token, create_token(0, *start, *type));
	else
		add_token(token, create_token(i - 1, *start + 1, *type));
	*start = &input[i] + 1;
	*type = get_type(input[i + 1]);
	return (i);
}

void    init_common_token(t_token **token, char *input, char **start, int *type)
{
    // printf("2. %d\n",*type);
    add_token(token, create_token((int)(input - *start), *start, *type));
    *start = input;
    *type = get_type(*input);
}


//lib_fnc
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned long n)
{
	if (!s1 || !s2)
		return (-1);
	while (n-- && (*(unsigned char *)s1 || *(unsigned char *)s2))
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		s1++;
		s2++;
	}
	return (0);
}