#ifndef ENVP_H
# define ENVP_H

typedef struct s_envp t_envp;

struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
	int		cnt;
};

#endif
