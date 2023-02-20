#include "minishell.h"
#include "expander.h"

static int  get_delete_len_and_check(char *str, int *check)
{
	int ret;
	char *start;
	char *quote;

	ret = 0;
	start = str;
	while (*start)
	{
		if (*start == '\'' || *start == '\"')
		{
			quote = ft_strchr(start + 1, *start);
			if (quote)
			{
				check[start - str] = 1;
				check[quote - str] = 1;
				start = quote;
				ret += 2;
			}
		}
		else if (*start == '*')
			*start = -42;
		start++;
	}
	return (ret);
}

static void get_delete_quote_string(char *str, int *check, char *ret, int len)
{
	int i;
	int now_len;

	i = 0;
	now_len = 0;
	while (i < len)
	{
		if (check[i] == 1)
		{
			++i;
			continue ;
		}
		ft_strlcat(ret, str + i, now_len + 2);
		++now_len;
		++i;
	}
}

int quote_delete(t_token *token)
{
	int del_len;
	int original_len;
	char    *ret;
	int *check;

	if (!token)
		return (1);
	original_len = ft_strlen(token->value);
	check = ft_calloc(original_len, sizeof(int));
	del_len = get_delete_len_and_check(token->value, check);
	ret = ft_calloc(original_len - del_len + 1, 1);
	if (!ret)
	{
		free(check);
		return (0);
	}
	get_delete_quote_string(token->value, check, ret, original_len);
	free(token->value);
	token->value = ret;
	free(check);
	return (1);
}