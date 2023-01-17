#ifndef CMD_H
# define CMD_H

#include "t_minishell.h"	//TODO remove?

typedef struct s_minishell t_minishell;
typedef struct s_cmd_tbl t_cmd_tbl;
typedef struct s_cmd t_cmd;

struct s_cmd_tbl
{
	int		cnt;
	t_cmd	*cmd;
};

struct s_cmd
{
	char	*cmd;
	void (*func)(t_minishell *minishell, char **arr);
	int		argc;
	char	*opt;
};

#endif