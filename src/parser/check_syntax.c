#include "parser.h"

int near_token_error(t_token *token)
{
	if (!first_token_error(token))
		return (0);
	if (!context_token_error(token))
		return (0);
	if (!last_token_error(token))
		return (0);
	return (1);
}

int match_error(t_token *token)
{
	if (!parenthesis_match_error(token))
		return (0);
	return (1);
}

int syntax_error_check(t_token *token)
{
	if (!near_token_error(token))
		return (0);
	if (!match_error(token))
		return (0);
	return (1);
}