#include "minishell.h"
#include "exec.h"

static int arr_size(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		token = token->next;
		size++;
	}
	return (size);
}

char	**make_cmd_arg(t_parse_tree *parse_tree)
{
	int		i;
	int		size;
	char	**cmd_arg;
	t_token	*temp;

	temp = parse_tree->token;

	i = 0;
	size = arr_size(parse_tree->token);
	cmd_arg = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		cmd_arg[i] = parse_tree->token->value;
		parse_tree->token = parse_tree->token->next;
		i++;
	}
	cmd_arg[i] = NULL;
	parse_tree->token = temp;
	return (cmd_arg);
}


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
void	get_cmd(t_minishell *minishell, t_arg *arg, t_parse_tree *parse_tree, char **envp)
{
	arg->path = get_path_envp(envp);
	// (void)parse_tree;
	// printf("%s\n",);
	// arg->cmd_arg = ft_split(av, ' ');
	arg->cmd_arg = make_cmd_arg(parse_tree);
	// arg->cmd_arg[0] = ft_substr(parse_tree->token->value, 0,  ft_strlen(parse_tree->token->value));
	// arg->cmd_arg[1] = ft_substr(parse_tree->token->next->value, 0, ft_strlen(parse_tree->token->next->value));

	// arg->cmd_arg[0] = "ls";
	// arg->cmd_arg[1] = "-a";

	// exit(0);
	if (arg->cmd_arg == NULL)
		shell_exit(minishell, 1, "error");
	arg->cmd = get_cmd_argv(arg->path, arg->cmd_arg[0]);
	if (arg->cmd == NULL )
		shell_exit(minishell, 1, "error3");
	// printf("%s\n",arg->cmd_arg[1]);
	
}
