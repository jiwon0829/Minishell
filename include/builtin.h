#include "types/t_cmd.h"

#define AC_ZERO		200		//명령어 인자 개수가 0인 경우
#define AC_LESS_1	201		// 명령어 인자 개수가 0 또는 1인 경우
#define AC_ANY		202		// 명령어 인자 개수가 제한 없는 경우(echo)

t_cmd_tbl	*init_cmd_tbl(void);

/*void	echo(t_minishell *minishell, char **arr);
void	cd(t_minishell *minishell, char **arr);
void	pwd(t_minishell *minishell, char **arr);
void	export(t_minishell *minishell, char **arr);
void	unset(t_minishell *minishell, char **arr);
void	env(t_minishell *minishell, char **arr);
void	ft_exit(t_minishell *minishell, char **arr);*/