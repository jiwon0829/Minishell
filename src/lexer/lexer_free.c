/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:19 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 15:56:22 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

// static void	free_dptr(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		arr[i] = NULL;
// 		i++;
// 	}
// 	free(arr);
// }

// static void	free_arg(t_arg *arg)
// {
// 	if (!arg)
// 		return ;
// 	free_dptr(arg->path);
// 	arg->path = NULL;
// 	free_dptr(arg->envp2);
// 	free_dptr(arg->cmd_arg);
// 	free(arg->cmd);
// 	free(arg);
// }

void	free_tokens(t_token *token)
{
	t_token	*node;

	node = token;
	while (node)
	{
		token = node->next;
		node->next = NULL;
		free(node->value);
		node->value = NULL;
		node->arg = NULL;
		free(node);
		node = token;
	}
	free(token);
	token = NULL;
}
