#include "builtin.h"

void	echo(t_minishell *minishell, char **arr)
{
	int	i;

	if (arr[1] && !ft_strncmp(arr[1], "-n", ft_strlen(arr[1])))
	{
		if (!arr[2])
			return ;	
		i = 2;
		while (arr[i])
		{
			printf("%s", arr[i++]);
			if (arr[i])
				printf(" ");
		}
	}
	else
	{
		if (arr[1])
		{
			i = 1;
			while (arr[i])
			{
				printf("%s", arr[i++]);
				if (arr[i])
					printf(" ");
			}
		}
		printf("\n");
	}
}
