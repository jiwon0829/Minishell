/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:51 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 10:37:01 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

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

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("^C", 1);
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putendl_fd("^\\Quit: 3", 2);
}
