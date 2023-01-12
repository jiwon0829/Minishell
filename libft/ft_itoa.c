/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:39:51 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/29 20:19:53 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(int num)
{
	size_t	len;

	len = 0;
	while (num)
	{
		++len;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*ptr;
	size_t		len;

	num = n;
	len = 0;
	if (num <= 0)
	{
		len = get_len(num) + 1;
		num *= -1;
	}
	else
		len = get_len(num);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ptr[len] = '\0';
	while (len > 0)
	{
		ptr[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
