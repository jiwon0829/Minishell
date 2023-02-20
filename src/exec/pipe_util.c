/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:25:07 by inosong           #+#    #+#             */
/*   Updated: 2023/02/15 10:10:25 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "redirect.h"

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

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp == NULL)
		return (NULL);
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
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, F_OK);
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

static int	check_cur_exec(t_minishell *minishell, t_arg *arg)
{
	int	fd;

	(void)minishell;
	fd = access(arg->cmd_arg[0], F_OK);
	if (fd != -1)
	{
		fd = access(arg->cmd_arg[0], X_OK);
		if (fd != -1)
		{
			arg->cmd = (arg->cmd_arg[0]);
			return (1);
		}
		return (-1);
	}
	return (0);
}

void	get_cmd(t_minishell *minishell, t_arg *arg,
	t_parse_tree *parse_tree, char **envp)
{
	int	i;

	i = 0;
	arg->cmd_arg = make_cmd_arg(parse_tree);
	if (arg->cmd_arg == NULL)
		shell_exit(minishell, 1, "cmd_empty");
	if (strncmp("./", *(arg->cmd_arg), 2) == 0)
		i = check_cur_exec(minishell, arg);
	if (i == 1 || i == -1)
	{
		if (i == -1)
		{
			redir_dup(minishell);
			permission_error_message(minishell, 126, *(arg->cmd_arg));
		}
	}
	else
	{
		if (strncmp("./", *(arg->cmd_arg), 2) == 0)
			redir_open_error_message(minishell, 127, *(arg->cmd_arg));
		arg->path = get_path_envp(envp);
		if (arg->path == NULL)
			redir_open_error_message(minishell, 127, *(arg->cmd_arg));
		arg->cmd = get_cmd_argv(arg->path, arg->cmd_arg[0]);
	}
}
