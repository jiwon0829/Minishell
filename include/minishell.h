/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:55:35 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:55:57 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "types/t_minishell.h"

# define FALSE 0
# define TRUE 1
# define FAILURE -1

void	main_loop(t_minishell *minishell);
void	init_envp(t_envp **node, char **envp);
void	init(t_minishell *minishell, char *envp[]);
void	free_all(t_parse_tree *parse_tree);

#endif
