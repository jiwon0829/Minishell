#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "types/t_minishell.h"

#define FALSE 0
#define TRUE 1

void	setting_signal(void);
void 	main_loop(t_minishell *minishell);
void	init(t_minishell *minishell, char *envp[]);


#endif
