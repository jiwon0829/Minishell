#include "minishell.h"
#include "expander.h"

static int find_type(char *str)
{
    char    type[5][3] = {"\'", "\"", "$?", "$", " "};
    int     i;

    i = 0;
    while (i < 5)
    {
        if (!ft_strncmp(str, type[i], ft_strlen(type[i])))
            return (i + 1);
        ++i;
    }
    return (0);
}

static void get_char_type(char *str, int *check)
{
    int type;

    while (*str)
    {
        type = find_type(str);
        str++;
        *check = type;
        check++;
        if (type == 3)
        {
            str++;
            *check = type;
            check++;
        }
    }
}

static void find_envp_key(int *check, int len)
{
    int i;

    i = 1;
    while(i < len)
    {
        if (check[i] == 0 && check[i - 1] == 4)
        {
            check[i] = 6;
            check[i - 1] = 7;
        }
        else if (check[i] ==0 && check[i - 1] == 6)
            check[i] = 6;
        ++i;
    }
    i = 0;
    while(i < len)
    {
        if (check[i] == 4)
            check[i] = 0;
        ++i;
    }
}

static void change_word_all(int *check, int start, int end)
{
    int i;

    i = start + 1;
    while(i < end)
        check[i++] = 0;
    check[start] = 8;
    check[end] = 8;
}

static void change_single_quote(int *check, int start, int end)
{
    int i;

    i = start + 1;
    while (i < end)
    {
        if (check[i] == 1)
            check[i] = 0;
        ++i;
    }
    check[start] = 8;
    check[end] = 8;
}

static void quote_in_envp(char *str, int *check)
{
    char    *start;
    char    *quote;

    start = str;
    while(*start)
    {
        if (*start == '\'')
        {
            quote = ft_strchr(start + 1, *start);
            if (quote)
            {
                change_word_all(check, start - str, quote - str);
                start = quote;
                //delete_len += 2;
            }
        }
        else if (*start == '\"')
        {
            quote = ft_strchr(start + 1, *start);
            if (quote)
            {
                change_single_quote(check, start - str, quote - str);
                start = quote;
                //delete_len += 2;
            }
        }
        start++;
    }
}

int	envp_expand(t_token *token)
{
	int	*check;
	int original_len = 0;

	if (!token)
		return (1);
	if (token->type == WORD && ft_strchr(token->value, '$'))
	{
		original_len = ft_strlen(token->value);
		check = ft_calloc(original_len, sizeof(int));
		get_char_type(token->value, check);	//1. 문자열 자리별 타입을 체크
		find_envp_key(check, original_len); //2. 일반문자-> envp key 찾아내기
		quote_in_envp(token->value, check);    //3. quote 처리
		//4. change_envp_value
        //5. split and inset token
	}
    printf("%s\n", token->value);
    for(int i=0;i < original_len;i++)
    {
        printf("%c[%d]\n", token->value[i], check[i]);
    }
	return (1);
}
