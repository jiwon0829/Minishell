/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:29:56 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:32:08 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	find_head_from_tail(t_token *tail, t_token **find, int type)
{
	int	parenthesis_cnt;

	parenthesis_cnt = 0;
	while (tail)
	{
		if (tail->type == PRNTH_LEFT)
			++parenthesis_cnt;
		else if (tail->type == PRNTH_RIGHT)
			--parenthesis_cnt;
		if (((type == LOGICAL && (is_logical(tail->type))) \
			|| (tail->type == type) || (type == REDIR && is_redir(tail->type))) \
			&& !parenthesis_cnt)
		{
			*find = tail;
			return (TRUE);
		}
		tail = tail->prev;
	}
	*find = NULL;
	return (FALSE);
}

int	find_head_from_head(t_token *head, t_token **find, int type)
{
	int	parenthesis_cnt;

	parenthesis_cnt = 0;
	while (head)
	{
		if (head->type == PRNTH_LEFT)
			++parenthesis_cnt;
		else if (head->type == PRNTH_RIGHT)
			--parenthesis_cnt;
		if ((head->type == type) && !parenthesis_cnt)
		{
			*find = head;
			return (TRUE);
		}
		head = head->next;
	}
	*find = NULL;
	return (FALSE);
}

void	go_left_node(t_parse_tree **parse_tree)
{
	t_token			*next_tail;
	t_parse_tree	*prev_tree;

	prev_tree = *parse_tree;
	parse_tree = &((*parse_tree)->left);
	next_tail = get_tail_token((*parse_tree)->token);
	parse_token(parse_tree, &next_tail, prev_tree);
}

void	go_right_node(t_parse_tree **parse_tree)
{
	t_token			*next_tail;
	t_parse_tree	*prev_tree;

	prev_tree = *parse_tree;
	parse_tree = &((*parse_tree)->right);
	next_tail = get_tail_token((*parse_tree)->token);
	parse_token(parse_tree, &next_tail, prev_tree);
}

void	parse_token(t_parse_tree **parse_tree, t_token **tail, \
				t_parse_tree *prev_tree)
{
	t_token	*find;

	check_parenthesis(parse_tree, tail);
	if (find_head_from_tail(*tail, &find, LOGICAL) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (find_head_from_tail(*tail, &find, PIPE) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (find_head_from_head((get_head_token(*tail)), &find, REDIR) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (!(*parse_tree) && *tail)
	{
		*parse_tree = init_parse_tree();
		(*parse_tree)->token = get_head_token(*tail);
		*tail = NULL;
		return ;
	}
	else
		return ;
	go_left_node(parse_tree);
	go_right_node(parse_tree);
}
