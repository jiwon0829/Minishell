#ifndef T_REDIRECT_H
# define T_REDIRECT_H

#include "t_exec.h"
#include "types/t_minishell.h"
#include "lexer.h"

typedef struct s_redirect t_redirect;
// # define INPUT 3
// # define OUTPUT_OVER 4
// # define HERE_DOC 5
// # define OUTPUT_APPEND 6
struct s_redirect
{
	int					fd[2];
	int					type;
	char				*file_name;
	struct	s_redirect	*next;
};

#endif