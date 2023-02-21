/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:24:44 by inosong           #+#    #+#             */
/*   Updated: 2023/02/21 19:05:24 by inosong          ###   ########.fr       */
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
#include "expander.h"
#include "t_expander.h"

void	get_change_dollor_str(t_minishell *minishell, t_expander *ex,
	t_parse_tree *parse_tree, int *i)
{
	ex->change_str = get_envpnode(minishell->envp, ex->middle_str)->value;
	ex->return_str = expen_strjoin(ex->first_str, ex->change_str);
	parse_tree->token->value = expen_strjoin(ex->return_str, ex->last_str);
	*i = strlen(ex->return_str) - 1 ;
}
