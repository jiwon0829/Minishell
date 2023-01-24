#include "builtin.h"

void	pwd(t_minishell *minishell, char **arr)
{
	char *path;

	(void)arr;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf("%s\n", path);
	free(path);
	path = NULL;
    minishell->exit_status = 100;//TODO
}
