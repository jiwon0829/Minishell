/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:20:16 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:21:25 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "envp.h"

static void	find_envp_key(int *check, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (check[i] == 0 && check[i - 1] == 4)
		{
			check[i] = 6;
			check[i - 1] = 7;
		}
		else if (check[i] == 0 && check[i - 1] == 6)
			check[i] = 6;
		++i;
	}
	i = 0;
	while (i < len)
	{
		if (check[i] == 4)
			check[i] = 0;
		++i;
	}
}

static int	quote_in_envp(char *str, int *check)
{
	char	*start;
	char	*quote;
	int		ret;

	ret = 0;
	start = str;
	while (*start)
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

static void	get_delete_char_string(char *str, int *check, char *ret, int len)
{
	int	i;
	int	now_len;

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

static void	change_envp_value(t_minishell *minishell, t_token *token, \
								int *check, char **ret)
{
	int		i;
	int		len;
	int		now_len;
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
			char *value = find_envp_value(minishell->envp, key);
			change_value(ret, key, value, &now_len);
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
		change_envp_value(minishell, token, check, &ret);
		free(token->value);
		token->value = ret;
		free(check);
	}
	return (1);
}
