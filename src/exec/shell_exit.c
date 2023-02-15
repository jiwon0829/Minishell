/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:27:31 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 11:27:31 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "error_message.h"

// char *make_err_msg(t_minishell *minishell, char *str1, char *str2, char *str3)
// {
// 	char	*ret_str;
// 	int		len;
// 	int		i;
// 	// int		j;

// 	ret_str = NULL;
// 	if (str1)
// 	{
// 		i = 0;
// 		while (str1)
// 		{
// 			ret_str[i] = str1[i];
// 			i++;
// 		}
// 	}
// 	if (str2)
// 	{
// 		len = ft_strlen(ret_str);
// 		i = 0;
// 		while (str2)
// 		{
// 			ret_str[len + i] = str2[i];
// 			i++;
// 		}
// 	}
// 	if (str3)
// 	{
// 		len = ft_strlen(ret_str);
// 		i = 0;
// 		while (str3)
// 		{
// 			ret_str[len + i] = str3[i];
// 			i++;
// 		}
// 	}
// 	return (ret_str);
// }

void	shell_err(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	err_massage(minishell, status, msg);
}

void	shell_exit(t_minishell *minishell, int status, char *msg)
{
	minishell->exit_status = status;
	exit_err_massage(minishell, status, msg);
}

void	exit_value_set(t_minishell *minishell, int exit_status)
{
	minishell->exit_status = exit_status;
}

//pipe에서 포크한 자식프로세스 종료할때
void	exit_err_massage(t_minishell *minishell, int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_status = status;
	exit(status);
}

//일반 실패 명령
void	err_massage(t_minishell *minishell, int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_status = status;
}
