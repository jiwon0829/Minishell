#ifndef T_EXEC_H
# define T_EXEC_H

// #include "t_parse_tree.h"
#include "t_parse_tree.h"


typedef struct s_arg t_arg;
typedef struct s_pipe t_pipe;
// typedef struct s_exec t_exec;

// struct s_exec
// {
// 	int fdstdout;	//표준출력
// 	int	fdstdin;	//표준입력
// 	int	fdout;      //redirection
// 	int	fdin;       //redirection
//     // int exit;
//     int eof_exit;
//     int redir_flag;
//     int heredoc_flag;
//     int export_flag;
// };

 struct s_arg{
	char	**path;
    char    **envp2;
	char	**cmd_arg;
	char	*cmd;
	int		pipe_fd[2];
	int		pid;  
};

struct s_pipe
{
	int				fd[2];
	struct s_pipe	*next;
	struct s_arg	*arg;
	int				pid;
};

#endif

