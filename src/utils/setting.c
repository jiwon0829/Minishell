#include "minishell.h"
#include "envp.h"

/*static void setting_shlvl(t_envp *envp)
{
	t_envp *shlvl_node;
	int shlvl;

}*/

#include "test_code.h"	//TODO
void	init(t_minishell *minishell, char *envp[])
{
	minishell->exit_status = 0;
	init_envp(&(minishell->envp), envp);
	//minishell->cmd_tbl = init_cmd_tbl();
	//print_envp(minishell->envp);	//TODO
	//setting_shlvl(minishell->envp);
}
