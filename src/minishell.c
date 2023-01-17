#include "../include/minishell.h"

void	a()
{
	printf("leaks test\n");
	system("leaks minishell");
}

int main(int ac, char *av[], char *envp[])
{
	//atexit(a);
	t_minishell	minishell;

	// check_arg(ac, av);
	// init(&minishell, envp);
	main_loop(&minishell);
	return (0);
}
