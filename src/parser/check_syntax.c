#include "parser.h"

int near_token_error(t_token *token)
{
	if (!first_token_error(token))  //pipe, and, or, ) 불가능
		return (0);
	if (!last_token_error(token))   //word, )만 가능
		return (0);
}

int match_error(t_token *token)
{
	if (!quote_match_error(token) || !parenthesis_match_error(token))
		return (0);
}

int syntax_error_check(t_token *token)
{
	if (!near_token_error(token))
		return (0);
	if (!match_error(token))
		return (0);
	return (1);
}