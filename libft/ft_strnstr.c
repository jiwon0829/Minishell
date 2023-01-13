/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:48:52 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/07/11 20:47:34 by jiwonhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while ((i + j) < len && haystack[i + j] && \
			haystack[i + j] == needle[j])
			{
				if (haystack[i + j] != needle[j])
					break ;
				++j;
			}
			if (!needle[j])
				return ((char *)haystack + i);
		}
		++i;
	}
	return (NULL);
}
