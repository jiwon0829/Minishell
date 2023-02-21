/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:38:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:16:22 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "lexer.h"
#include <dirent.h>

static int	find_valid_value(char *dname, char *find)
{
	int	dname_len;
	int	find_len;
	int	i;
	int	j;

	dname_len = ft_strlen(dname);
	find_len = ft_strlen(find);
	i = 0;
	while (i < dname_len && i < find_len && (dname[i] == find[i]))
		++i;
	if (find_len == i)
		return (dname_len == i);
	if (find[i] == -42)
	{
		j = 0;
		while (i + j <= dname_len)
		{
			if (find_valid_value(dname + j + i, find + i + 1))
				return (1);
			++j;
		}
	}
	return (0);
}

static int	add_result_token(t_token *token, char *dname, int *cnt)
{
	char	*new_value;
	t_token	*new_token;

	if (!(*cnt))
	{
		new_value = ft_strdup(dname);
		if (!new_value)
			return (0);
		free(token->value);
		token->value = new_value;
	}
	else
	{
		new_token = create_token(ft_strlen(dname) + 1, dname, WORD);
		if (token->next)
		{
			token->next->prev = new_token;
			new_token->next = token->next;
		}
		token->next = new_token;
		new_token->prev = token;
	}
	(*cnt)++;
	return (1);
}

static void	reset_token_value(char *str)
{
	while (*str)
	{
		if (*str == -42)
			*str = 42;
		str++;
	}
}

static int	is_valid_wildcard(t_token *token, char *find)
{
	struct dirent	*dirent;
	DIR				*dir;
	int				cnt;

	dir = opendir(".");
	if (!dir)
		return (0);
	cnt = 0;
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (find_valid_value(dirent->d_name, find) && \
			!add_result_token(token, dirent->d_name, &cnt))
		{
			closedir(dir);
			return (0);
		}
	}
	if (!cnt)
		reset_token_value(token->value);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}

int	wildcard(t_token *token)
{
	char	*find;

	if (!token)
		return (1);
	if (token->type == WORD && ft_strchr(token->value, -42))
	{
		find = ft_strdup(token->value);
		if (!find || !is_valid_wildcard(token, find))
		{
			free(find);
			return (0);
		}
		free(find);
		find = NULL;
	}
	return (1);
}
