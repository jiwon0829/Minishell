/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:13:39 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 13:13:56 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "error_message.h"
#include "t_cmd.h"
#include "stdio.h"
#include "lexer.h"
#include "error_message.h"
#include "redirect.h"

void	set_redirect(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token		*tmp_token;
	t_redirect	*redirect;

	minishell->heredoc_cnt = 0;
	tmp_token = parse_tree->token;
	while (tmp_token)
	{
		if (tmp_token->type == INPUT || tmp_token->type == OUTPUT_OVER || \
			tmp_token->type == HERE_DOC || tmp_token->type == OUTPUT_APPEND)
		{
			redirect = redir_lstnew(tmp_token->type, tmp_token->next->value);
			if (tmp_token->type == HERE_DOC)
				minishell->heredoc_cnt++;
			redir_lstadd_back(&(minishell->redirect), redirect);
			tmp_token = tmp_token->next->next;
		}
		else
		{
			tmp_token = tmp_token->next;
		}
	}
}
