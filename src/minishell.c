/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:49:38 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 01:50:17 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_arg(int ac, char *av[])
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_minishell	minishell;

	check_arg(ac, av);
	init(&minishell, envp);
	// system("leaks minishell");
	main_loop(&minishell);
	return (minishell.exit_status);
}
