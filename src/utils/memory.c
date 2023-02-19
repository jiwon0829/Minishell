/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:31:35 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/17 16:18:39 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void	free_parse_tree(t_parse_tree *tree)
{
	// printf("in free_parse_tree\n");
	if (tree->left)
		free_parse_tree(tree->left);
	if (tree->right)
		free_parse_tree(tree->right);
	free_tokens(tree->token);
	tree->token = NULL;
	free(tree);
}

void	free_all(t_parse_tree *parse_tree)
{
	// printf("in free_all\n");
	if (!parse_tree)
		return ;
	free_parse_tree(parse_tree);
}
