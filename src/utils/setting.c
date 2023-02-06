#include "minishell.h"
#include "envp.h"
#include "builtin.h"

static void setting_shlvl(t_envp *envp)
{
	t_envp *shlvl_node;
	int shlvl;

	shlvl_node = get_envpNode(envp, "SHLVL");
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
	// minishell = (t_minishell *)malloc(sizeof(*minishell));
	setting_signal();
	minishell->exit_status = 0;
	init_envp(&(minishell->envp), envp);
	minishell->cmd_tbl = init_cmd_tbl();
	setting_shlvl(minishell->envp);
	minishell->redirect = NULL;
	minishell->heredoc = NULL;
}
