#ifndef T_EXEC_H
# define T_EXEC_H

// #include "t_parse_tree.h"
#include "t_parse_tree.h"
#include "t_token.h"



typedef struct s_pipe t_pipe;

 

struct s_pipe
{
	int				fd[2];
	struct s_pipe	*next;
	// struct s_arg	*arg;
	int				pid;
	int				fdin;
	int				fdout;
};

#endif

