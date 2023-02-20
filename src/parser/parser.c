/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:06:13 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 15:49:52 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

t_parse_tree	*parser(t_minishell *minishell, t_token *token)
{
	t_parse_tree	*parse_tree;
	t_token			*tail;

	if (!syntax_error_check(token))
	{
		free_token(token);
		minishell->exit_status = 258;
		return (NULL);
	}
	parse_tree = NULL;
	tail = get_tail_token(token);
	parse_token(&parse_tree, &tail, NULL);
	return (parse_tree);
}
