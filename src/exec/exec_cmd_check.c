/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:13:13 by inosong           #+#    #+#             */
/*   Updated: 2023/02/20 15:37:53 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "redirect.h"

int	check_arg_type(t_minishell *minishell, t_arg *arg)
{
	int	i;

	(void)minishell;
	i = 0;
	if (strncmp("./", *(arg->cmd_arg), 2) == 0
		|| strncmp("/", *(arg->cmd_arg), 1) == 0)
		i = 1;
	return (i);
}
