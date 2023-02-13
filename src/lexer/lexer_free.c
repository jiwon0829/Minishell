/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:19 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 18:17:42 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_token	*free_tokens(t_token *token)
{
	t_token	*temp;

	if (!token)
		return (NULL);
	temp = token;
	while (token)
	{
		token = token->next;
		free(temp);
		temp = token;
	}
	return (NULL);
}
