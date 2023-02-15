/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:31:35 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/15 17:12:58 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void	free_parse_tree(t_parse_tree *tree)
{
	if (!tree->left && !tree->right)
	{
		if (tree->token)
			free_tokens(tree->token);
		tree->token = NULL;
		free(tree);
		tree = NULL;
		return ;
	}
	if (tree->left)
		free_parse_tree(tree->left);
	if (tree->right)
		free_parse_tree(tree->right);
}

void	free_all(t_parse_tree *parse_tree, t_token *token)
{
	if (!parse_tree && !token)
		return ;
	if (parse_tree)
		free_parse_tree(parse_tree);
	// free(parse_tree);
	// parse_tree = NULL;

	// if (parse_tree)
	// {
	// 	if (parse_tree->token)
	// 		free_tokens(parse_tree->token);
	// }

	// if (token)
	// 	free_tokens(token);
}
