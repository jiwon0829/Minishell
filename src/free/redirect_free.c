/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:48:45 by inosong           #+#    #+#             */
/*   Updated: 2023/02/20 15:48:53 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "heredoc.h"
#include "expander.h"
#include "signals.h"

void	free_redirect(t_minishell *minishell)
{
	t_redirect	*tmp;
	t_redirect	*free_redirect;

	free_redirect = minishell->redirect;
	while (free_redirect)
	{
		tmp = free_redirect->next;
		free(free_redirect->file_name);
		free(free_redirect);
		free_redirect = tmp;
	}
	minishell->redirect = NULL;
}
