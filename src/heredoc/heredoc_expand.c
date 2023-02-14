/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:09 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 15:47:59 by inosong          ###   ########.fr       */
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
#include "expander.h"

int	heredoc_remove_dollor(t_minishell *minishell, char **value, int *i)
{
	t_expander	expand;

	init_expander(&expand);
	(void)minishell;
	expand.j = *i + 1;
	while (value[0][expand.j])
	{
		if (value[0][expand.j] == '?')
		{
			heredoc_expand_exit_status(minishell, value, i, expand.j);
			expand.exit_flag = 1;
			break ;
		}
		if (value[0][expand.j] == '$' || value[0][expand.j] == '\''
			|| value[0][expand.j] == '"' || value[0][expand.j] == ' ')
			break ;
		expand.j++;
	}
	if (expand.exit_flag == 0)
	{
		heredoc_expand_dollor(minishell, &expand, value, i);
	}
	return (expand.ret);
}

void	heredoc_remove_squotes(t_minishell *minishell, char **value, int *i)
{
	t_expander	expand;

	init_expander(&expand);
	(void)minishell;
	expand.j = *i + 1;
	expand.first_str = expand_substr(*value, 0, *i);
	while (value[0][expand.j] != '\'')
	{
		expand.j++;
	}
	expand.k = expand.j + 1;
	while (value[0][expand.k])
		expand.k++;
	expand.middle_str = ft_substr(*value, *i + 1, expand.j - *i - 1);
	expand.return_str = expen_strjoin(expand.first_str, expand.middle_str);
	*i = strlen(expand.return_str) - 1;
	expand.last_str = ft_substr(*value, expand.j + 1, expand.k - expand.j + 1);
	free(*value);
	*value = expen_strjoin(expand.return_str, expand.last_str);
}

void	heredoc_remove_dquotes(t_minishell *minishell, char **value, int *i)
{
	t_expander	expand;

	init_expander(&expand);
	(void)minishell;
	expand.j = *i + 1;
	expand.first_str = ft_substr(*value, 0, *i);
	while (value[0][expand.j] != '"')
		expand.j++;
	expand.k = expand.j + 1;
	while (value[0][expand.k])
		expand.k++;
	expand.middle_str = ft_substr(*value, *i + 1, expand.j - *i - 1);
	expand.return_str = expen_strjoin(expand.first_str, expand.middle_str);
	*i = strlen(expand.return_str) - 1;
	expand.last_str = ft_substr(*value, expand.j + 1, expand.k - expand.j + 1);
	free(*value);
	*value = expen_strjoin(expand.return_str, expand.last_str);
}

char	*heredoc_expander(t_minishell *minishell,
	t_heredoc *heredoc, char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			heredoc_remove_squotes(minishell, &value, &i);
			heredoc->quote_flag = 1;
		}
		else if (value[i] == '"')
		{
			heredoc_remove_dquotes(minishell, &value, &i);
			heredoc->quote_flag = 1;
		}
		if (i >= 0 && !value[i])
			break ;
		i = i + 1;
	}
	return (value);
}

void	*heredoc_dollor_expander(t_minishell *minishell,
	t_heredoc *heredoc, char **value)
{
	int	i;

	(void)heredoc;
	i = 0;
	while (value[0][i])
	{
		if (value[0][i] == '$')
		{
			if (heredoc_remove_dollor(minishell, value, &i) == 1)
				i--;
		}
		if (i >= 0 && !value[0][i])
			break ;
		i = i + 1;
	}
	return (*value);
}
