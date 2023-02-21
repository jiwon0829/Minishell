/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:39:23 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 18:23:01 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "envp.h"

void	get_delete_char_string(char *str, int *check, char *ret, int len)
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

void	change_exit_status_value(t_minishell *minishell, char **ret, \
								int *now_len)
{
	int		len;
	char	*status;
	char	*head;
	char	*tail;

	len = ft_strlen(*ret);
	status = ft_itoa(minishell->exit_status);
	tail = ft_substr(*ret, 0, *now_len);
	head = ft_strjoin(tail, status);
	free(tail);
	tail = ft_substr(*ret, *now_len + 2, len - *now_len - 2);
	free(*ret);
	*ret = ft_strjoin(head, tail);
	*now_len += ft_strlen(status);
	free(status);
	free(head);
	free(tail);
}

char	*get_key_in_string(int *check, char *str, int *i)
{
	char	*ret;
	int		len;
	int		limit;

	len = 0;
	limit = ft_strlen(str);
	while (limit > *i + len + 1 && check[*i + len + 1])
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

void	change_value(char **ret, char *key, char *value, int *now_len)
{
	int		value_len;
	int		original_len;
	char	*head;
	char	*tail;

	value_len = ft_strlen(value);
	original_len = ft_strlen(*ret);
	if (value)
	{
		tail = ft_substr(*ret, 0, *now_len);
		head = ft_strjoin(tail, value);
		free(tail);
	}
	else
		head = ft_substr(*ret, 0, *now_len);
	tail = ft_substr(*ret, *now_len + (int)ft_strlen(key) + 1, \
			original_len - *now_len - ft_strlen(key) + 1);
	free(*ret);
	if (!ft_strlen(head) && !ft_strlen(tail))
		*ret = ft_calloc(1, 1);
	else
		*ret = ft_strjoin(head, tail);
	*now_len += value_len;
	free(head);
	free(tail);
}

void	change_envp_value(t_minishell *minishell, t_token *token, \
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
			--now_len;
		if (check[i] == 3)
		{
			change_exit_status_value(minishell, ret, &now_len);
			i += 2;
			continue ;
		}
		if (check[i] == 7)
		{
			key = get_key_in_string(check, token->value, &i);
			change_value(ret, key, find_envp_value(minishell->envp, key), \
						&now_len);
			free(key);
			continue ;
		}
		++i;
		++now_len;
	}
}
