/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:44:24 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/07/11 16:44:51 by jiwonhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoc(int num, int fd)
{
	int	tmp;

	tmp = num % 10;
	if (!num)
		return ;
	num /= 10;
	itoc(num, fd);
	ft_putchar_fd('0' + tmp, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	long long	tmp;

	if (fd < 0)
		return ;
	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	tmp = num % 10;
	itoc(num / 10, fd);
	ft_putchar_fd('0' + tmp, fd);
}
