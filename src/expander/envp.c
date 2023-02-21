#include "minishell.h"
#include "expander.h"
#include "envp.h"

void find_envp_key(int *check, int len)
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

void change_word_all(int *check, int start, int end)
{
	int i;

	i = start + 1;
	while(i < end)
		check[i++] = 0;
	check[start] = 8;
	check[end] = 8;
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
		change_envp_value(minishell, token, check, &ret);
		free(token->value);
		token->value = ret;
		free(check);
	}
	return (1);
}
