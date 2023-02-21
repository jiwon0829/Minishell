/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:31:35 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:10:05 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void	free_parse_tree(t_parse_tree *tree)
{
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
	if (!parse_tree)
		return ;
	free_parse_tree(parse_tree);
}
