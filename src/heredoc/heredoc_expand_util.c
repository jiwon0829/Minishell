/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:00:35 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 10:43:44 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "heredoc.h"
#include "expander.h"
#include "signals.h"
#include "t_expander.h"

void	heredoc_expand_dollor(t_minishell *minishell, t_expander *exp,
	char **value, int *i)
{
	exp->first_str = expand_substr(*value, 0, *i);
	exp->k = exp->j;
	while (value[0][exp->k])
		exp->k++;
	exp->middle_str = ft_substr(*value, *i + 1, exp->j - *i - 1);
	exp->last_str = expand_substr(*value, exp->j, exp->k - exp->j + 1);
	free(*value);
	if (get_envpnode(minishell->envp, exp->middle_str))
	{
		exp->change_str = get_envpnode(minishell->envp, exp->middle_str)->value;
		exp->return_str = expen_strjoin(exp->first_str,
				exp->change_str);
		*value = expen_strjoin(exp->return_str, exp->last_str);
		*i = strlen(exp->return_str) - 1 ;
	}
	else
	{
		*value = expen_strjoin(exp->first_str, exp->last_str);
		if (!exp->first_str)
			*i = 0;
		else
			*i = strlen(exp->first_str);
		exp->ret = 1;
	}
}

void	heredoc_expand_exit_status(t_minishell *minishell,
	char **value, int *i, int j)
{
	t_expander	expand;

	init_expander(&expand);
	expand.first_str = expand_substr(*value, 0, *i);
	expand.k = j;
	while (value[0][expand.k])
		expand.k++;
	expand.last_str = expand_substr(*value, j + 1, expand.k - j + 1);
	free(*value);
	expand.change_str = ft_itoa(minishell->exit_status);
	expand.return_str = expen_strjoin(expand.first_str, expand.change_str);
	*value = expen_strjoin(expand.return_str, expand.last_str);
	*i = strlen(expand.return_str) - 1 ;
}
