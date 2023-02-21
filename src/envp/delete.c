/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:26:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 19:26:24 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "../../libft/libft.h"

void	delete_envp(t_envp *head)
{
	t_envp	*node;

	node = head;
	while (node)
	{
		head = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = head;
	}
	free(head);
}
