/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:09:46 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/15 15:50:14 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir(int type)
{
	if (type == INPUT || type == OUTPUT_OVER || type == HERE_DOC \
		|| type == OUTPUT_APPEND)
		return (TRUE);
	return (FALSE);
}

int	is_logical(int type)
{
	if (type == LOGICAL_AND || type == LOGICAL_OR)
		return (TRUE);
	return (FALSE);
}

int	is_valid_prev_prnth_left(int type)
{
	if (type != LOGICAL_AND && type != LOGICAL_OR \
		&& type != PIPE && type != PRNTH_LEFT)
		return (TRUE);
	return (FALSE);
}

char	*tokentostring(t_token *token)
{
	char	*ret;
	t_token	*tmp;

	ret = malloc(1);
	tmp = token;
	while (tmp)
	{
		ret = ft_strjoin(ret, tmp->value);
		tmp = tmp->next;
	}
	return (ret);
}
