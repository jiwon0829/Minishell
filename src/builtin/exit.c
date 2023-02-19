/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:34:05 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/15 14:52:22 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error_message.h"

static long long	ft_atoll(char *num)
{
	int			i;
	int			check;
	long long	ret;
	long long	val;

	ret = 0;
	i = 0;
	check = 1;
	if (num[i] == '-')
	{
		i = 1;
		check = -1;
	}
	while (num[i])
	{
		val = ret;
		ret = ret * 10 + (num[i++] - '0');
		if (val > ret)
		{
			exit_argment_error(num);
			exit (255);
		}
	}
	return (ret * check);
}

static int	is_valid_value(char *arr)
{
	int	i;

	i = 0;
	if (arr[i] == '-')
		++i;
	while (arr[i])
		if (!ft_isdigit(arr[i++]))
			return (0);
	return (1);
}

void	ft_exit(t_minishell *minishell, char **arr)
{
	if (arr[1] && arr[2])
	{
		exit_argment_cnt_error();
		minishell->exit_status = 255;
		return ;
	}
	else if (!arr[1])
	{
		ft_putstr_fd("exit\n", 2);
		minishell->exit_status = 0;
	}
	else if (!is_valid_value(arr[1]))
	{
		exit_argment_error(arr[1]);
		minishell->exit_status = 255;
	}
	else
	{
		minishell->exit_status = (int)(ft_atoll(arr[1]) % 256);
		ft_putstr_fd("exit\n", 2);
	}
	// system("leaks minishell");
	exit(minishell->exit_status);
}
