/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:44 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 01:39:37 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "envp.h"

int	update_path(t_envp *head)
{
	char	*oldpwd;
	char	*pwd;

	if (!find_envp(head, "OLDPWD"))
		insert_envp(&head, "OLDPWD", NULL);
	oldpwd = find_envp_value(head, "PWD");
	if (!oldpwd)
		update_envp(head, "OLDPWD", NULL);
	else
		update_envp(head, "OLDPWD", oldpwd);
	if (find_envp(head, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		update_envp(head, "PWD", pwd);
		free(pwd);
	}
	return (0);
}

int	go_to_home(t_envp *envp)
{
	char	*home;

	home = find_envp_value(envp, "HOME");
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (update_path(envp));
}

int	go_to_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = find_envp_value(envp, "OLDPWD");
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(oldpwd))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(oldpwd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	else
		ft_putendl_fd(oldpwd, 1);
	return (update_path(envp));
}

int	go_to_new(t_envp *envp, char *path)
{
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (update_path(envp));
}

void	cd(t_minishell *minishell, char **arr)
{
	if (!arr[1] || !ft_strncmp(arr[1], "~", 1))
		minishell->exit_status = go_to_home(minishell->envp);
	else if (!ft_strncmp(arr[1], "-", 1))
		minishell->exit_status = go_to_oldpwd(minishell->envp);
	else
		minishell->exit_status = go_to_new(minishell->envp, arr[1]);
}
