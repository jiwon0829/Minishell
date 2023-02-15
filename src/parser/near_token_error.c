/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   near_token_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:07:29 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:23:30 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error_message.h"

int	first_token_error(t_token *token)
{
	if (token && (token->type == LOGICAL_AND || token->type == LOGICAL_OR \
		|| token->type == PIPE || token->type == PRNTH_RIGHT))
		return (snytax_error_message(token->value));
	return (1);
}

int	last_token_error(t_token *token)
{
	t_token	*node;

	node = token;
	while (node && node->next)
		node = node->next;
	if (node && (node->type == WORD || node->type == PRNTH_RIGHT))
		return (1);
	return (snytax_error_message("newline"));
}

int	context_token_error(t_token *token)
{
	while (token)
	{
		if (!token->prev)
			;
		else if (is_logical(token->type) || token->type == PIPE)
		{
			if (token->prev->type != WORD && token->prev->type != PRNTH_RIGHT)
				return (snytax_error_message(token->value));
		}
		else if (is_redir(token->type) && is_redir(token->prev->type))
			return (snytax_error_message(token->value));
		else if (token->type == PRNTH_LEFT \
				&& is_valid_prev_prnth_left(token->prev->type))
			return (snytax_error_message(token->value));
		else if (token->type == PRNTH_RIGHT)
		{
			if (token->prev->type != WORD && token->prev->type != PRNTH_RIGHT)
				return (snytax_error_message(token->value));
		}
		else if (token->type == WORD && token->prev->type == PRNTH_RIGHT)
			return (snytax_error_message(token->value));
		token = token->next;
	}
	return (1);
}
