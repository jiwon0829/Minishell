/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:08:55 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:09:58 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"

void	export_error_message(char *msg)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	unset_error_message(char *msg)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": invalid parameter name\n", 2);
}

int	snytax_error_message(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 1);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

void	exit_argment_error(char *msg)
{
	ft_putstr_fd("exit\nminishell: exit:", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	exit_argment_cnt_error(void)
{
	ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
}
