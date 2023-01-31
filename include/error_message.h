#include <stdio.h>
#include "t_minishell.h"
#include "../libft/libft.h"

void	export_error_message(char *msg);
void	unset_error_message(char *msg);
void	exit_err_massage(t_minishell *minishell, int status, char *msg);
void	err_massage(t_minishell *minishell, int status, char *msg);
