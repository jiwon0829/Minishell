/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:31:35 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 18:41:35 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void free_parse_tree(t_parse_tree *tree)
{
	if (tree->left)
		free_parse_tree(tree->left);
	tree->left = NULL;
	if (tree->right)
		free_parse_tree(tree->right);
	tree->right = NULL;
	if (tree->token)
		free_tokens(tree->token);
	tree->token = NULL;
}
void	free_all(t_parse_tree *parse_tree, t_token *token)
{
	if (!parse_tree && !token)
		return ;
	if (parse_tree)
	{
		free_parse_tree(parse_tree)
	}
	if (token)
		free_tokens(token);
	free(token);
	token = NULL;	//main_loop
}
