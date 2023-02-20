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
	while (check[*i + len])
	{
		if (check[*i + len + 1] == 6)
			++len;
		else
			break ;
	}
	ret = ft_substr(str, *i + 1, len);
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
	tail = ft_substr(ret, *now_len + (int)ft_strlen(key) + 1, len - ft_strlen(key));
	free(ret);
	ret = ft_strjoin(head, tail);
	*now_len += value_len;
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
	while (i < len)
	{
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

int	envp_expand(t_minishell *minishell, t_token *token, int *is_expand)
{
	int		*check;
	int		original_len = 0;
	char	*ret = NULL;
	int		del_len;

	if (!token)
		return (1);
	if (token->type == WORD && ft_strchr(token->value, '$'))
	{
*is_expand = 1;
		original_len = ft_strlen(token->value);
		check = ft_calloc(original_len, sizeof(int));
		get_char_type(token->value, check);
		find_envp_key(check, original_len);
		del_len = quote_in_envp(token->value, check);
		ret = ft_calloc(original_len - del_len + 1, 1);
		if (!ret)
		{
			free(check);
			return (0);
		}
		get_delete_char_string(token->value, check, ret, original_len);
		change_envp_value(minishell, token, check, ret);
		free(token->value);
		if (!ret)
			ret = ft_strdup("");
		token->value = ret;
		//5. split and inset token
	}
	return (1);
}
