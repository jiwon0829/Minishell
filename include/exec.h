#ifndef EXEC.H
# define EXEC.H

#include "minishell.h"

//fd
#define STDIN 0
#define STDOUT 0
#define STDERR 0

//exit code
#define SUCCESS 0
#define SYNTAXERROR 1
#define UNEXPTOKEN 2
#define NOCOMMAND 127
#define NOEXECUTE 126
#define REDIRERROR 139


typedef struct s_exec
{
	int fdstdout;	//표준출력
	int	fdstdin;	//표준입력
	int	fdout;      //redirection
	int	fdin;       //redirection
    // int exit;
    int eof_exit;
    int redir_flag;
    int heredoc_flag;
    int export_flag;
}	t_exec;

#endif