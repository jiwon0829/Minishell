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
{
	if (sig == SIGINT)
	{
	write(2, "\n", 1);
	exit(128 + SIGINT);
	}
}

void	setting_signal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, prompt_handler);	// CTRL + C
	signal(SIGQUIT, SIG_IGN);	// CTRL + /
}

static void sigint_handler(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("^C", 1);
}

static void sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putendl_fd("^\\Quit: 3", 2);
}

void	setting_child(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}