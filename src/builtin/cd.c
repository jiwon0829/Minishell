#include "builtin.h"

t_envp	*find_value(t_envp *head, char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	return (head);
}

void	update_path(t_envp **head, char *key, char *value)
{
	while (*head && ft_strncmp((*head)->key, key, ft_strlen(key) + 1))
		head = &((*head)->next);
	if (*head)
	{
		free((*head)->value);
		(*head)->value = ft_strdup(value);
	}
}

void	go_to_home(t_envp *envp)
{
	t_envp	*home;
	char	*currentpwd;

	home = find_value(envp, "HOME");
	if (!home)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", home->value);
	free(currentpwd);
}

void	go_to_oldpwd(t_envp *envp)
{
	t_envp	*oldpwd;
	char	*currentpwd;

	oldpwd = find_value(envp, "OLDPWD");
	if (!oldpwd)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", oldpwd->value);
	free(currentpwd);

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
void	go_to_new(t_envp *envp, char *path)
{
    char    **cdpath;
	char	*currentpwd;
	char	*new_path;

    cdpath = NULL;
    if (find_value(envp, "CDPATH"))
        cdpath = ft_split(find_value(envp, "CDPATH")->value, ':');
	currentpwd = getcwd(NULL, 0);
	new_path = find_cdpath(&cdpath, path);
	if (!new_path)
		new_path = ft_strdup(path);
	if (chdir(new_path) == -1)
	{
		printf("cd error\n");
		free(currentpwd);
		free(path);
		return ;
	}
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", new_path);
	free(currentpwd);
	free(new_path);
}

void	cd(t_minishell *minishell, char **arr)
{
	printf(">>Before\nHOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME")->value, find_value(minishell->envp, "PWD")->value, find_value(minishell->envp, "OLDPWD")->value);
	if (!arr[1])
		go_to_home(minishell->envp);
	else if (!ft_strncmp(arr[1], "-", 1))
		go_to_oldpwd(minishell->envp);
	else
		go_to_new(minishell->envp, arr[1]);
	printf(">>After\nHOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME")->value, find_value(minishell->envp, "PWD")->value, find_value(minishell->envp, "OLDPWD")->value);
}
