#ifndef T_CMD_H
# define T_CMD_H

#include "t_minishell.h"

//typedef struct s_minishell t_minishell;

typedef struct s_cmd
{
	char	*cmd;
	void (*func)(t_minishell *minishell, char **arr);
	int		argc;
	char	*opt;
}				t_cmd;

typedef struct s_cmd_tbl
{
	int		cnt;
	t_cmd	*cmd;
}				t_cmd_tbl;

#endif
