#include "parser.h"

t_parse_tree *parser(t_token *token)
{
	t_parse_tree	*parse_tree;
	t_token			*tail;
	
	if (!syntax_error_check(token))
		return (NULL);
	parse_tree = NULL;
	tail = get_tail_token(token);
	parse_token(&parse_tree, &tail, NULL);
	return (parse_tree);
}
