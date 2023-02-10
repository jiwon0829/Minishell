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
	int				left_flag;
	int				right_flag;
	// struct s_arg	*arg;
	int				pid;
	int				fdin;
	int				fdout;
	// t_redirect	*redir;
	// t_heredoc *hedoc;
};

#endif

