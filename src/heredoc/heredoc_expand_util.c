/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:00:35 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 15:09:41 by inosong          ###   ########.fr       */
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
#include "term_signal.h"
#include "t_expander.h"

void	heredoc_expand_dollor(t_minishell *minishell, t_expander *expan,
	char **value, int *i)
{
	expan->first_str = expand_substr(*value, 0, *i);
	expan->k = expan->j;
	while (value[0][expan->k])
		expan->k++;
	expan->middle_str = ft_substr(*value, *i + 1, expan->j - *i - 1);
	expan->last_str = expand_substr(*value, expan->j, expan->k - expan->j + 1);
	free(*value);
	if (get_envpNode(minishell->envp, expan->middle_str))
	{
		expan->change_str = get_envpNode(minishell->envp,
				expan->middle_str)->value;
		expan->return_str = expen_strjoin(expan->first_str,
				expan->change_str);
		*value = expen_strjoin(expan->return_str, expan->last_str);
		*i = strlen(expan->return_str) - 1 ;
	}
	else
	{
		*value = expen_strjoin(expan->first_str, expan->last_str);
		if (!expan->first_str)
			*i = 0;
		else
			*i = strlen(expan->first_str);
		expan->ret = 1;
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
