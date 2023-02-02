#include <stdio.h>
#include "minishell.h"
#include "../libft/libft.h"

void	export_error_message(char *msg);
void	unset_error_message(char *msg);
int	snytax_error_message(char   *msg);
void	exit_err_massage(t_minishell *minishell, int status, char *msg);
void	err_massage(t_minishell *minishell, int status, char *msg);
int	snytax_error_message(char   *msg);
void	exit_argment_error(char *msg);
void	exit_argment_cnt_error();