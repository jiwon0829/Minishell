#ifndef T_PARSE_TREE_H
# define T_PARSE_TREE_H

#include "t_token.h"

typedef struct s_parse_tree t_parse_tree;

struct s_parse_tree
{
	t_parse_tree	*up;
	t_parse_tree	*left;
	t_parse_tree	*right;
	t_token			*token;
	int         	type;
};

#endif