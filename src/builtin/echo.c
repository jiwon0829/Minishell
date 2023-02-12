#include "builtin.h"

void	echo(t_minishell *minishell, char **arr)
{
	int	is_n_option;
	int	i;

	if (!arr[1])
	{
		printf("\n");
		minishell->exit_status = 0;
		return ;
	}
	is_n_option = 0;
	i = 1;
	if (arr[1] && ft_strchr(arr[1], '-'))
	{
		if (ft_strstr(arr[1], "-n"))
			is_n_option = 1;
		++i;
	}
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == 0)
		{
			i++;
			continue ;
		}
		printf("%s", arr[i++]);
		if (arr[i])
			printf(" ");
	}
	if (!is_n_option)
		printf("\n");
	minishell->exit_status = 0;
}
