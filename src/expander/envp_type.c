/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:40:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 18:10:59 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "envp.h"

int	find_type(char *str)
{
	char	*type[5];
	int		i;

	i = 0;
	type[0] = "\'";
	type[1] = "\"";
	type[2] = "$?";
	type[3] = "$";
	type[4] = " ";
	while (i < 5)
	{
		if (!ft_strncmp(str, type[i], ft_strlen(type[i])))
			return (i + 1);
		++i;
	}
	return (0);
}

void	get_char_type(char *str, int *check)
{
	int	type;

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

void	change_single_quote(int *check, int start, int end)
{
	int	i;

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

int	quote_in_envp(char *str, int *check)
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
