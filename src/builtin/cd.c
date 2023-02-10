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
		return (1);
	if (chdir(home))
		return (1);
	return (update_path(envp));
}

int	go_to_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = find_envp_value(envp, "OLDPWD");
	if (!oldpwd)
		return (1);
	if (chdir(oldpwd))
		return (1);
	return (update_path(envp));
}

char    *find_cdpath(char ***cdpath, const char *path)
{
    int     i;
    char    *ret;
    char    *tmp;
    struct stat stat;

    if (!*cdpath)
        return (NULL);
    ret = ft_strjoin("/", path);
    i = 0;
    while ((*cdpath)[i])
    {
        tmp = ft_strjoin((*cdpath)[i], ret);
        free(ret);
        ret = tmp;
        if (!lstat(ret, &stat))
        {
            free(cdpath);
            return (ret);
        }
        ++i;
    }
    free(cdpath);
    return (NULL);
}

int	go_to_new(t_envp *envp, char *path)
{
    char    **cdpath;
	char	*new_path;

    cdpath = NULL;
    if (find_envp(envp, "CDPATH"))
        cdpath = ft_split(find_envp(envp, "CDPATH")->value, ':');
	new_path = find_cdpath(&cdpath, path);
	if (!new_path)
		new_path = ft_strdup(path);
	if (chdir(new_path))
	{
		printf("cd error\n");
		free(path);
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
