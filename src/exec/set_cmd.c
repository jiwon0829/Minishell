/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:25:37 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 11:27:18 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "redirect.h"
#include "builtin.h"

static void free_redirection(t_minishell *minishell, t_token *token)
{
	(void)minishell;
	
	free(token->value);
	token->value = NULL;
	free(token);
}

static void	pass_tree_token(t_minishell *minishell, t_parse_tree *parse_tree)
{
	(void)minishell;
	t_token *tmp;

	while (parse_tree->token)
	{
		if (parse_tree->token->type >= INPUT
			&& parse_tree->token->type <= OUTPUT_APPEND)
			{
				tmp = parse_tree->token->next->next;
				free_redirection(minishell, parse_tree->token->next);
				free_redirection(minishell, parse_tree->token);
				parse_tree->token = tmp;
			}
		else
			break ;
	}
}

static void	delete_not_word_token(t_minishell *minishell,
	t_parse_tree *parse_tree)
{
	t_token *tmp;
	t_token *prev;

	(void)minishell;
	while (parse_tree->token)
	{
		if (parse_tree->token->type >= INPUT
			&& parse_tree->token->type <= OUTPUT_APPEND)
		{
			// printf("del_re_tok\n");
			tmp = parse_tree->token->next->next;
			prev = parse_tree->token->prev;
			parse_tree->token->prev->next = tmp;
			free_redirection(minishell, parse_tree->token->next);
			free_redirection(minishell, parse_tree->token);
			parse_tree->token = tmp;
			if (parse_tree->token)
				parse_tree->token->prev = prev;
		}
		else
			parse_tree->token = parse_tree->token->next;
	}
}

void	set_cmd(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*tmp_token;

	(void)minishell;
	if (parse_tree->token->type == WORD)
		;
	else
	{
		pass_tree_token(minishell, parse_tree);
	}
	tmp_token = parse_tree->token;
	delete_not_word_token(minishell, parse_tree);
	parse_tree->token = tmp_token;
}
