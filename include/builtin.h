#include <stdio.h>
#include "minishell.h"
#include "error_message.h"
#include "types/t_cmd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "envp.h"

#define AC_ZERO		200		//명령어 인자 개수가 0인 경우
#define AC_LESS_1	201		// 명령어 인자 개수가 0 또는 1인 경우
#define AC_ANY		202		// 명령어 인자 개수가 제한 없는 경우(echo)

#define EXIT_NO -1
#define EXIT_NON_NUM -2
#define EXIT_MANY -3

#define FALSE 0
#define TRUE 1

t_cmd_tbl	*init_cmd_tbl(void);
int	check_builtin_arg(t_cmd *cmd, char **arr);
int	check_builtin(t_cmd_tbl *cmd_tbl, const char *cmd);
void	ft_execve(t_minishell *minishell, t_cmd_tbl *cmd_tbl, char **arr);

void	echo(t_minishell *minishell, char **arr);
void	cd(t_minishell *minishell, char **arr);
void	pwd(t_minishell *minishell, char **arr);
void	export(t_minishell *minishell, char **arr);
void	unset(t_minishell *minishell, char **arr);
void	env(t_minishell *minishell, char **arr);
void	ft_exit(t_minishell *minishell, char **arr);