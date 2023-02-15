/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:03:22 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:30:36 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*get_head_token(t_token *token)
{
	while (token && token->prev)
		token = token->prev;
	return (token);
}

t_token	*get_tail_token(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

void	set_left_token(t_token *token, t_token *find)
{
	if (!token)
		return ;
	while (token && (token->next != find))
		token = token->next;
	if (token)
		token->next = NULL;
}

void	set_left_token_redirection(t_parse_tree *parse_tree, t_token *token)
{
	t_token	*left_tail;

	left_tail = get_tail_token(parse_tree->token);
	if (token->next->next)
	{
		if (left_tail)
		{
			left_tail->next = token->next->next;
			left_tail->next->prev = left_tail;
		}
		else
		{
			parse_tree->token = token->next->next;
			parse_tree->token->prev = NULL;
		}
		token->next->next = NULL;
	}
}
