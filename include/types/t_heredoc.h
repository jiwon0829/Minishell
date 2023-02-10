#ifndef T_HEREDOC_H
# define T_HEREDOC_H

#include "t_parse_tree.h"
#include "t_token.h"

typedef struct s_heredoc t_heredoc;



struct s_heredoc
{
	int			fd[2];
	int			pid;
	char		*limit;
	t_heredoc	*next;
	// struct s_arg	*arg;
};

#endif