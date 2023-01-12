/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:27:46 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/08/07 14:15:48 by jiwonhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_range_check(char const *str, size_t i, int sign)
{
	unsigned long long	val;
	unsigned long long	res;

	res = 0;
	while (ft_isdigit(str[i]))
	{
		val = res;
		res = res * 10 + (str[i] - '0');
		if (val > res && sign == -1)
			return (0);
		else if (val > res && sign == 1)
			return (-1);
		++i;
	}
	return (sign * res);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	return (ft_range_check(str, i, sign));
}
