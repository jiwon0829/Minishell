#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>
#include <sys/ioctl.h>
#include "types/t_minishell.h"

enum e_signum
{
	DEFAULT,
	CATCH,
	IGNORE
};

void	set_signal(int sigint, int sigquit);
void	prompt_handler(int sig);
void	heredoc_handler(int sig);
void	sigquit_handler(int sig);

#endif