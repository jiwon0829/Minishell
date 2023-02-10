#include "term_signal.h"

void	prompt_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	heredoc_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)sig;
}

void	parent_handler(int sig)
{
	write(STDIN_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	setting_signal(void)
{
	signal(SIGINT, prompt_handler);	// CTRL + C
	signal(SIGQUIT, SIG_IGN);	// CTRL + /
}

void	setting_term(t_minishell *minishell)
{
	tcgetattr(STDIN_FILENO, &(minishell->prev_term));
	tcgetattr(STDIN_FILENO, &(minishell->term));
	minishell->term.c_cflag &= ~ECHOCTL;
	minishell->term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->term));
}