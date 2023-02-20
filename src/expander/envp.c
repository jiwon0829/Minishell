#include "minishell.h"
#include "expander.h"
#include "envp.h"

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

static int quote_in_envp(char *str, int *check)
{
	char    *start;
	char    *quote;
	int     ret;

	ret = 0;
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
				ret += 2;
			}
		}
		else if (*start == '\"')
		{
			quote = ft_strchr(start + 1, *start);
			if (quote)
			{
				change_single_quote(check, start - str, quote - str);
				start = quote;
				ret += 2;
			}
		}
		start++;
	}
	return (ret);
}

static void get_delete_char_string(char *str, int *check, char *ret, int len)
{
	int i;
	int now_len;

	i = 0;
	now_len = 0;
	while (i < len)
	{
		if (check[i] == 8)
		{
			++i;
			continue ;
		}
		ft_strlcat(ret, str + i, now_len + 2);
		++now_len;
		++i;
	}
}

// void	change_envp_value(t_minishell *minishell, t_token *token, int *check, int len)
// {
// 	int	end;	//key를 기준으로 왼쪽 마지막
// 	int	start;	//key를 기준으로 오른쪽 처음
// 	char	*ret;
// 	char	*head;
// 	char	*status;

// 	end = 0;
// 	ret = malloc(1);
// 	while (end < len)	//check전체를 돌면서
// 	{
// 		if (check[end] == 8)
// 		{
// 			++end;
// 			continue;
// 		}
// 		if (check[end] == 3)
// 		{
// 			status = ft_itoa(minishell->exit_status);
// 			head = ft_strjoin(ret, status);
// 			free(status);free(ret);
// 			start = end + 2;
// 			ret = ft_strjoin(head, ft_substr(token->value, start, len - start + 1));
// 			free(head);
// 		}
// 		else if (check[end] == 7)
// 		{
// 			//ret + end부터 check[start++] == 6인 부분을 찾아서 key와 start 구하기
// 			//get key->value && is_split
// 			//strjoin(strjoin(strsub(0, end - 1), value), strsub(start, original_len));
// 		}
// 		else
// 			ft_strlcat(ret, token->value + end, end + 2);
// 		++end;
// 	}
// }

static void	change_exit_status_value(t_minishell *minishell, char *ret, int *now_len)
{
	int		len;
	char	*status;
	char	*head;
	char	*tail;

	len = ft_strlen(ret);
	status = ft_itoa(minishell->exit_status);
	head = ft_strjoin(ft_substr(ret, 0, *now_len), status);
	tail = ft_substr(ret, *now_len + 2, len - *now_len - 2);
	free(ret);
	ret = ft_strjoin(head, tail);
	*now_len += ft_strlen(status);
	free(status);
	free(head);
	free(tail);
}

static char *get_key_in_string(int *check, char *str, int *i)
{
	char	*ret;
	int		len;

	len = 0;
	while (check[*i + len + 1])
	{
		if (check[*i + len] != 6)
			break ;
		++len;
	}
	printf(">>%d\n", len + 1);
	ret = ft_substr(str, *i + 1, len + 1);
	*i += len + 1;
	return (ret);
}

static void	change_value(char *ret, char *key, char *value, int *now_len)
{
	int	value_len;
	int	len;
	char	*head;
	char	*tail;

	value_len = ft_strlen(value);
	len = ft_strlen(ret);
	head = ft_strjoin(ft_substr(ret, 0, *now_len), value);
	tail = ft_substr(ret, *now_len + ft_strlen(key) + 1, len - ft_strlen(key));
	free(ret);
	ret = ft_strjoin(head, tail);
	*now_len += value_len;
	(*now_len)--;
	free(head);free(tail);
}
static void	change_envp_value(t_minishell *minishell, t_token *token, int *check, char *ret)
{
	int	i;
	int	len;
	int	now_len;
	char	*key;

	i = 0;
	len = ft_strlen(token->value);
	now_len = 0;
	printf("str: %s\tret: %s\n", token->value, ret);	//TODO
	while (i < len)
	{printf("[%c(%d)] %s\n", token->value[i], check[i], ret);
		if (check[i] == 8)
		{
			++i;
			continue ;
		}
		if (check[i] == 3)
		{
			change_exit_status_value(minishell, ret, &now_len);
			i += 2;
			continue ;
		}
		if (check[i] == 7)
		{
			key = get_key_in_string(check, token->value, &i);
			change_value(ret, key, find_envp_value(minishell->envp, key), &now_len);
			free(key);
			continue ;
		}
		++i;
		++now_len;
	}
}

int	envp_expand(t_minishell *minishell, t_token *token)
{
	int		*check;
	int		original_len = 0;
	char	*ret = NULL;
	int		del_len;

	if (!token)
		return (1);
	if (token->type == WORD && ft_strchr(token->value, '$'))
	{
		original_len = ft_strlen(token->value);
		check = ft_calloc(original_len, sizeof(int));
		get_char_type(token->value, check);	//1. 문자열 자리별 타입을 체크
		find_envp_key(check, original_len); //2. 일반문자-> envp key 찾아내기
		del_len = quote_in_envp(token->value, check);    //3. quote 처리
		ret = ft_calloc(original_len - del_len + 1, 1);
		if (!ret)
		{
			free(check);
			return (0);
		}
		get_delete_char_string(token->value, check, ret, original_len);
		change_envp_value(minishell, token, check, ret);
		free(token->value);
		token->value = ret;
		//change_envp_value(minishell, token, check, original_len);//4. change_envp_value
		//5. split and inset token
	}
	// printf("%s(%s)\n", token->value, ret);
	// for(int i=0;i < original_len;i++)
	// {
	// 	printf("%c[%d]\n", token->value[i], check[i]);
	// }
	(void)minishell;
	return (1);
}
