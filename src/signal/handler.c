/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:51 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 15:38:58 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

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

void	sigquit_handler(int sig)
{(void)sig;
	ft_putendl_fd("Quit: 3\n", 1);
}

void	set_signal(int sigint, int sigquit)
{
	{
		if (sigint == DEFAULT)
			signal(SIGINT, SIG_DFL);
		else if (sigint == CATCH)
			signal(SIGINT, prompt_handler);
		else if (sigint == IGNORE)
			signal(SIGINT, SIG_IGN);
	}
	{
		if (sigquit == DEFAULT)
			signal(SIGQUIT, SIG_DFL);
		else if (sigquit == CATCH)
			signal(SIGQUIT, sigquit_handler);
		else if (sigquit == IGNORE)
			signal(SIGQUIT, SIG_IGN);
	}
}
