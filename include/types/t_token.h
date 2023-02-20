#ifndef T_TOKEN_H
# define T_TOKEN_H

typedef struct s_token t_token;
typedef struct s_arg t_arg;

 struct s_arg{
	char	**path;
	char	**envp2;
	char	**cmd_arg;
	char	*cmd;
	int		pipe_fd[2];
	int		pid;
};
struct s_token
{
	//int		expand;
	char	*value;
	int		len;
	int		type;
	int		fd_in;
	int		fd_out;
	t_arg	*arg;
	t_token	*prev;
	t_token	*next;
};

#endif