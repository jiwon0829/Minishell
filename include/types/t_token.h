#ifndef T_TOKEN_H
# define T_TOKEN_H

typedef struct s_token t_token;

struct s_token
{
	int		fd_in;
	int		fd_out;
	char	*tok;
	char	*value;
	int		len;
	int		type;
	t_token	*prev;
	t_token	*next;
};

#endif