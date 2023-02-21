/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:31:51 by inosong           #+#    #+#             */
/*   Updated: 2023/02/21 16:59:46 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "envp.h"


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
