/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:10:26 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:10:26 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "envp.h"
#include "builtin.h"
#include "signals.h"

static void	setting_shlvl(t_envp *envp)
{
	t_envp	*shlvl_node;
	int		shlvl;
	char	*shlvl_str;

	shlvl_node = get_envpnode(envp, "SHLVL");
	if (!shlvl_node)
	{
		insert_envp(&envp, "SHLVL", "1");
		return ;
	}
	shlvl = ft_atoi(shlvl_node->value);
	++shlvl;
	shlvl_str = ft_itoa(shlvl);
	update_envp(envp, "SHLVL", shlvl_str);
	free(shlvl_str);
}

	//TODO
void	init(t_minishell *minishell, char *envp[])
{
	set_signal(CATCH, IGNORE);
	minishell->exit_status = 0;
	init_envp(&(minishell->envp), envp);
	minishell->cmd_tbl = init_cmd_tbl();
	setting_shlvl(minishell->envp);
	minishell->pipe_cnt = 0;
	minishell->heredoc_cnt = 0;
	minishell->redirect = NULL;
	minishell->heredoc = NULL;
	minishell->heredoc_cnt = 0;
	minishell->scmd_builtin = 0;
	minishell->inchild = 0;
}
