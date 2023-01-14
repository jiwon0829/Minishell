#ifndef T_MINISHELL_H
# define T_MINISHELL_H

#include "t_envp.h"
#include "t_cmd.h"

typedef struct s_minishell t_minishell;

struct s_minishell
{
	int			exit_status;
	char 		**path;
	t_cmd_tbl	*cmd_tbl;
};


#endif
