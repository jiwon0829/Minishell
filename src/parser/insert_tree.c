/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:02:21 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:31:14 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parse_tree	*init_parse_tree(void)
{
	t_parse_tree	*ret;

	ret = (t_parse_tree *)malloc(sizeof(t_parse_tree));
	ft_memset(ret, 0, sizeof(t_parse_tree));
	ret->type = WORD;
	return (ret);
}

void	set_new_node(t_parse_tree *new_node, t_parse_tree *prev_tree, \
t_token *find)
{
	new_node->up = prev_tree;
	new_node->token = find;
	new_node->type = find->type;
}

void	get_left_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->left = init_parse_tree();
	parse_tree->left->up = parse_tree;
	parse_tree->left->token = get_head_token(token);
	if (parse_tree->left->token == token)
		parse_tree->left->token = NULL;
	parse_tree->left->type = WORD;
	set_left_token(parse_tree->left->token, token);
	token->prev = NULL;
	if (is_redir(token->type))
		set_left_token_redirection(parse_tree->left, token);
}

void	get_right_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->right = init_parse_tree();
	parse_tree->right->up = parse_tree;
	parse_tree->right->token = token->next;
	parse_tree->right->token->prev = NULL;
	parse_tree->right->type = WORD;
	token->next = NULL;
	if (is_redir(token->type))
		parse_tree->right->token->next = NULL;
}

void	insert_tree(t_parse_tree **parse_tree, t_token *find, \
					t_parse_tree *prev_tree)
{
	t_parse_tree	*new_tree;

	new_tree = init_parse_tree();
	set_new_node(new_tree, prev_tree, find);
	get_left_node(new_tree, find);
	get_right_node(new_tree, find);
	if (parse_tree && *parse_tree)
	{
		free(*parse_tree);
		*parse_tree = NULL;
	}
	*parse_tree = new_tree;
}
