#ifndef T_ENVP_H
# define T_ENVP_H

typedef struct s_envp t_envp;

struct s_envp
{
	char	*key;
	char	*value;
	int		is_shell;
	t_envp	*next;
	int		cnt;
};

#endif
