/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:02:11 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/07/11 18:35:47 by jiwonhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split_free(char ***result, size_t cnt)
{
	while (--cnt)
	{
		free((*result)[cnt]);
		(*result)[cnt] = 0;
	}
	free(*result);
	*result = 0;
	return (NULL);
}

static char	**word_malloc(char **result, char const *s, char c, size_t wordcnt)
{
	size_t	i;
	size_t	cnt;
	size_t	start;

	i = 0;
	cnt = 0;
	start = 0;
	while (s[i] && cnt < wordcnt)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				++i;
			result[cnt++] = ft_substr(s, start, i - start);
			if (!result)
				return (split_free(&result, cnt));
		}
		else
			++i;
	}
	result[cnt] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	wordcnt;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	wordcnt = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			++wordcnt;
			while (s[i] && s[i] != c)
				++i;
		}
		else
			++i;
	}
	result = (char **)malloc(sizeof(char *) * (wordcnt + 1));
	if (!result)
		return (0);
	return (word_malloc(result, s, c, wordcnt));
}
