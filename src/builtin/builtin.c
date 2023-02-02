#include "builtin.h"

static void	setting_cmd(t_cmd *cmd, char *command, int argc, char *option)
{
	cmd->cmd = command;
	cmd->argc = argc;
	cmd->opt = option;
}

t_cmd_tbl	*init_cmd_tbl(void)
{
    t_cmd_tbl	*cmd_tbl;
	
	cmd_tbl = (t_cmd_tbl *)malloc(sizeof(t_cmd_tbl));
	if (!cmd_tbl)
		exit(-1);	//TODO error message
	cmd_tbl->cnt = 7;
	cmd_tbl->cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_tbl->cnt);
	if (!cmd_tbl->cmd)
		exit(-1);	//TODO error message
	setting_cmd(&cmd_tbl->cmd[0], ft_strdup("echo"), AC_ANY, "");
	//cmd_tbl->cmd[0].func = echo;
	setting_cmd(&cmd_tbl->cmd[1], "cd", AC_LESS_1, "");
	//cmd_tbl->cmd[1].func = cd;
	setting_cmd(&cmd_tbl->cmd[2], "pwd", AC_ZERO, "");
	//cmd_tbl->cmd[2].func = pwd;
	setting_cmd(&cmd_tbl->cmd[3], "export", 0, "");
	//cmd_tbl->cmd[3].func = export;
	setting_cmd(&cmd_tbl->cmd[4], "unset", 0, "");
	//cmd_tbl->cmd[4].func = unset;
	setting_cmd(&cmd_tbl->cmd[5], "env", 0, "");
	//cmd_tbl->cmd[5].func = env;
	setting_cmd(&cmd_tbl->cmd[6], "exit", AC_ZERO, "");
	cmd_tbl->cmd[6].func = ft_exit;
	return (cmd_tbl);
}

int	check_builtin(t_cmd_tbl *cmd_tbl, const char *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd_tbl->cnt)
	{
		if (ft_strncmp(cmd_tbl->cmd[i].cmd, cmd, ft_strlen(cmd)) == 0)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_execve(t_minishell *minishell, t_cmd_tbl *cmd_tbl, char **arr)
{
	int	i;
	i = -1;
	while (++i < cmd_tbl->cnt)
	{
		if (ft_strncmp(cmd_tbl->cmd[i].cmd, arr[0], ft_strlen(arr[0])) == 0)
		{
			cmd_tbl->cmd[i].func(minishell, arr);
			return ;
		}
	}
}
