#include "minishell.h"
#include "signal.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			exit (1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGTERM)
	{
		write(STDOUT_FILENO, "exit\n", 1);sleep(10);
		exit (-1);
	}
	else
		return ;
}

void	setting_signal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handler);	// CTRL + C
	signal(SIGTERM, SIG_IGN);	// CTRL + D
	signal(SIGQUIT, SIG_IGN);	// CTRL + /
}
