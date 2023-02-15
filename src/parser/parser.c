/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:06:13 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:06:28 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parse_tree	*parser(t_token *token)
{
	t_parse_tree	*parse_tree;
	t_token			*tail;

	if (!syntax_error_check(token))
		return (NULL);
	parse_tree = NULL;
	tail = get_tail_token(token);
	parse_token(&parse_tree, &tail, NULL);
	return (parse_tree);
}
