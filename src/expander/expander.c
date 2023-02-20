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
#include "expander.h"
#include "envp.h"
#include "test_code.h"

void	expander(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*token;
	int		check;

	token = parse_tree->token;
	check = 0;
	while (token)
	{
		if (!envp_expand(minishell, token, &check) || !quote_delete(token, check) || !wildcard(token))
		{
			minishell->exit_status = 1;
			return ;
		}
		token = token->next;
	}
}
