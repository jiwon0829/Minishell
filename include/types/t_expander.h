#ifndef T_EXPENDER_H
# define T_EXPENDER_H

// #include "t_parse_tree.h"

typedef struct s_expander t_expander;

struct s_expander
{
	int		ret;
	int		j;
	int		k;
	int		exit_flag;
	char	*first_str;
	char	*middle_str;
	char	*change_str;
	char	*last_str;
	char	*return_str;
};

#endif
