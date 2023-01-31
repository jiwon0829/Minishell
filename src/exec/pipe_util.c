#include "minishell.h"
#include "t_exec.h"
#include "exec.h"
#include "error_message.h"

char	**get_path_envp(char *envp[])
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd_argv(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	path_cmd = ft_strjoin("/", cmd);
	fd = 0;
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
}

//t_minishell 자리가 없어서 exit status 전역변수 하나 하는게 어떨지 -> 수정하다가 자리생겼음
void	get_cmd(t_minishell *minishell, t_arg *arg, char *av, char **envp)
{
	arg->path = get_path_envp(envp);
	arg->cmd_arg = ft_split(av, ' ');
	if (arg->cmd_arg == NULL)
		shell_exit(minishell, 1, "error");
	arg->cmd = get_cmd_argv(arg->path, arg->cmd_arg[0]);
	if (arg->cmd == NULL )
		shell_exit(minishell, 1, "error");
}
