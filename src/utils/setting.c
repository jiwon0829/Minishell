#include "minishell.h"
#include "envp.h"
#include "builtin.h"
#include "signals.h"

static void setting_shlvl(t_envp *envp)
{
	t_envp *shlvl_node;
	int shlvl;

	shlvl_node = get_envpnode(envp, "SHLVL");
	if (!shlvl_node)
	{
		insert_envp(&envp, "SHLVL", "1");
		return ;
	}
	shlvl = ft_atoi(shlvl_node->value);
	++shlvl;
	insert_envp(&envp, "SHLVL", ft_itoa(shlvl));
}

#include "test_code.h"	//TODO
void	init(t_minishell *minishell, char *envp[])
{
	set_signal(CATCH, IGNORE);
	minishell->exit_status = 0;
	init_envp(&(minishell->envp), envp);
	minishell->cmd_tbl = init_cmd_tbl();
	setting_shlvl(minishell->envp);
	minishell->redirect = NULL;
	minishell->heredoc = NULL;
	minishell->heredoc_cnt = 0;
}
