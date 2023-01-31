#include "error_message.h"
#include "t_minishell.h"
#include "exec.h"

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

//pipe에서 포크한 자식프로세스 종료할때
void	exit_err_massage(t_minishell *minishell, int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_status = status;
	exit(status);
}

//일반 실패 명령
void	err_massage(t_minishell *minishell, int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_status = status;
}
