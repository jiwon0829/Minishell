/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:31:51 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 13:14:51 by inosong          ###   ########.fr       */
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
#include "expander.h"
#include "t_expander.h"


int	remove_dollor(t_minishell *minishell,
	t_parse_tree *parse_tree, int *i, int check)
{
	t_expander	expander;
	(void)check;
	// int			init;

	// init = *i;
	init_expander(&expander);
	(void)minishell;
	expander.j = *i + 1;
	while (parse_tree->token->value[expander.j])
	{
		if (parse_tree->token->value[expander.j] == '?')
		{
			expand_exit_status(minishell, parse_tree, i, expander.j);
			expander.exit_flag = 1;
			break ;
		}
		if (parse_tree->token->value[expander.j] == '$'
			|| parse_tree->token->value[expander.j] == '\''
			|| parse_tree->token->value[expander.j] == '"'
			|| parse_tree->token->value[expander.j] == ' ')
			break ;
		expander.j++;
	}
	if (expander.exit_flag == 0)
	{
		expand_dollor(minishell, &expander, parse_tree, i);
	}
	// if (check)
	// 	is_split_token(parse_tree, init, i);
	return (expander.ret);
}

void	remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
{
	t_expander	expander;

	init_expander(&expander);
	(void)minishell;
	expander.j = *i + 1;
	expander.first_str = ft_substr(parse_tree->token->value, 0, *i);
	while (parse_tree->token->value[expander.j] != '\'')
		expander.j++;
	expander.k = expander.j + 1;
	while (parse_tree->token->value[expander.k])
		expander.k++;
	expander.middle_str = ft_substr(parse_tree->token->value, *i + 1,
			expander.j - *i - 1);
	expander.return_str = expen_strjoin(expander.first_str,
			expander.middle_str);
	*i = strlen(expander.return_str) - 1;
	expander.last_str = ft_substr(parse_tree->token->value,
			expander.j + 1, expander.k - expander.j + 1);
	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(expander.return_str,
			expander.last_str);
}

void	remove_dquotes(t_minishell *minishell, t_parse_tree *parse, int *i)
{
	t_expander	exp;

	init_expander(&exp);
	(void)minishell;
	exp.j = *i + 1;
	exp.first_str = ft_substr(parse->token->value, 0, *i);
	while (parse->token->value[exp.j] != '"')
	{
		if (parse->token->value[exp.j] == '$')
		{
			if (remove_dollor(minishell, parse, &(exp.j), 0) == 1)
				exp.j--;
		}
		exp.j++;
	}
	exp.k = exp.j + 1;
	while (parse->token->value[exp.k])
		exp.k++;
	exp.middle_str = ft_substr(parse->token->value, *i + 1, exp.j - *i - 1);
	exp.return_str = expen_strjoin(exp.first_str, exp.middle_str);
	*i = strlen(exp.return_str) - 1;
	exp.last_str = ft_substr(parse->token->value,
			exp.j + 1, exp.k - exp.j + 1);
	free(parse->token->value);
	parse->token->value = expen_strjoin(exp.return_str, exp.last_str);
	free(exp.first_str);free(exp.middle_str);free(exp.last_str);free(exp.return_str);
}

void	expander(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*tmp_token;
	int		i;

	if (parse_tree->type == WORD)
		is_wildcard(parse_tree->token);
	tmp_token = parse_tree->token;
	while (parse_tree->token)
	{
		i = 0;
		while (parse_tree->token->value[i])
		{
			if (parse_tree->token->value[i] == '$')
			{
				remove_dollor(minishell, parse_tree, &i, 1);
				if (!parse_tree->token)
					break ;
			}
			if (parse_tree->token->value[i] == '\'')
				remove_squotes(minishell, parse_tree, &i);
			else if (parse_tree->token->value[i] == '"')
				remove_dquotes(minishell, parse_tree, &i);
			if (i >= 0 && !parse_tree->token->value[i])
				break ;
			i = i + 1;
		}
		if (parse_tree->token)
			parse_tree->token = parse_tree->token->next;
	}
	parse_tree->token = tmp_token;
}
