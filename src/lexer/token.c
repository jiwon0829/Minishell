/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:19:55 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/15 00:46:22 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include "lexer.h"

t_token	*create_token(int length, char *start, int type)
{
	t_token	*token;

	if (!length && !(type == DQUOT || type == SQUOT))
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->len = length;
	token->next = NULL;
	token->prev = NULL;
	token->value = ft_substr(start, 0, length);
	token->type = type;
	return (token);
}

void	add_token(t_token **first, t_token *to_add)
{
	t_token	*temp;

	if (!to_add)
	{
		return ;
	}
	if (!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
	to_add->prev = temp;
}

void	insert_token(t_token **tail, t_token *to_add)
{
	if (!to_add)
		return ;
	
	if (!(*tail)->prev)
	{
		(*tail)->prev = to_add;
		to_add->next = (*tail);
		return ;
	}
	(*tail)->prev->next = to_add;
	to_add->prev = (*tail)->prev;
	(*tail)->prev = to_add;
	to_add->next = (*tail);
}

void	del_token(t_token **target)
{
	t_token *del;
	t_token	*next;

	del = *target;
	next = (*target)->next;
	if (del->prev)
		(*target)->prev->next = (*target)->next;
	if (del->next)
		(*target)->next->prev = (*target)->prev;
	free(del->value);
	free(del);
	*target = next;
}