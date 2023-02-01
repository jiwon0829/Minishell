#include "error_message.h"

void	export_error_message(char *msg)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	unset_error_message(char *msg)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": invalid parameter name\n", 2);
}

int	snytax_error_message(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 1);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}
