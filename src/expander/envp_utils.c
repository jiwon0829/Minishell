/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:17:05 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:19:30 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "envp.h"

int find_type(char *str)
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

static void	change_exit_status_value(t_minishell *minishell, char **ret, int *now_len)
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

static void	change_value(char **ret, char *key, char *value, int *now_len)
{
	int	value_len;
	int	original_len;
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
	tail = ft_substr(*ret, *now_len + (int)ft_strlen(key) + 1, original_len - *now_len - ft_strlen(key) + 1);
	free(*ret);
	if (!ft_strlen(head) && !ft_strlen(tail))
		*ret = ft_calloc(1, 1);
	else
		*ret = ft_strjoin(head, tail);
	*now_len += value_len;
	free(head);free(tail);
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
