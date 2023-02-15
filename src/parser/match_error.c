/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:13:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:13:33 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error_message.h"

int	parenthesis_match_error(t_token *token)
{
	t_token	*node;
	int		cnt;

	cnt = 0;
	node = token;
	while (node)
	{
		if (node->type == PRNTH_LEFT)
			++cnt;
		else if (node->type == PRNTH_RIGHT)
			--cnt;
		node = node->next;
	}
	if (cnt > 0)
		return (snytax_error_message(")"));
	return (1);
}
