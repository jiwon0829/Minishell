#include "builtin.h"

int	n_option_echo(char **arr)
{
	int	i;

	if (!arr[2])
		return (1);	
	i = 2;
	while (arr[i])
	{
		printf("%s", arr[i++]);
		if (arr[i])
			printf(" ");
	}
	return (0);
}

void	echo(t_minishell *minishell, char **arr)
{
	int	i;

	if (arr[1] && !ft_strncmp(arr[1], "-n", ft_strlen(arr[1])))
		minishell->exit_status = n_option_echo(arr);
	else if (arr[1])
	{
		i = 1;
		while (arr[i])
		{
			printf("%s", arr[i++]);
			if (arr[i])
				printf(" ");
		}
		printf("\n");
		minishell->exit_status = 0;
	}
	else
		minishell->exit_status = 1;
}
