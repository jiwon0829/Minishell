/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:17:39 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 21:09:23 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_arr_echo(char **arr, int i)
{
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == 0)
		{
			++i;
			continue ;
		}
		if (ft_strlen(arr[i]))
			printf("%s", arr[i]);
		++i;
		if (arr[i])
			printf(" ");
	}
}

void	echo(t_minishell *minishell, char **arr)
{
	int	is_n_option;
	int	i;

	if (!arr[1])
	{
		printf("\n");
		minishell->exit_status = 0;
		return ;
	}
	is_n_option = 0;
	i = 1;
	if (arr[1] && ft_strchr(arr[1], '-'))
	{
		if (ft_strstr(arr[1], "-n"))
			is_n_option = 1;
		++i;
	}
	print_arr_echo(arr, i);
	if (!is_n_option)
		printf("\n");
	minishell->exit_status = 0;
}
