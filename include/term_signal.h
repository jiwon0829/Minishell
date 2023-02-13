#ifndef TERM_SIGNAL_H
# define TERM_SIGNAL_H

#include <termios.h>
#include <term.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "types/t_minishell.h"

void	setting_signal(void);
void	setting_child(void);
void	prompt_handler(int sig);
void	heredoc_handler(int sig);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

#endif