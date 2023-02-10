#include "term_signal.h"

void	prompt_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			exit (1);
		rl_replace_line("", 1);
		rl_redisplay();

	}
}

void	heredoc_handler(int sig)
{(void)sig;
	write(2, "\n", 1);
	exit(128 + SIGINT);
}

void	setting_signal(void)
{
	signal(SIGINT, prompt_handler);	// CTRL + C
	signal(SIGQUIT, SIG_IGN);	// CTRL + /
}
