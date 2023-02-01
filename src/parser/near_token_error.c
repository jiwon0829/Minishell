#include "parser.h"
#include "error_message.h"

int first_token_error(t_token *token)
{
	if (token && (token->type == LOGICAL_AND || token->type == LOGICAL_OR \
		|| token->type == PIPE || token->type == PRNTH_RIGHT))
		return (snytax_error_message(token->value));
	return (1);
}

int last_token_error(t_token *token)
{
	t_token *node;

	node = token;
	while (node && node->next)
		node = node->next;
	if (node && (node->type == WORD || node->type == PRNTH_RIGHT))
		return (1);
	return (snytax_error_message("newline"));
}

int context_token_error(t_token *token)
{
	while (token)
	{
		if (!token->prev)
			;
		else if (token->type == LOGICAL_AND || token->type == LOGICAL_OR || \
			token->type == PIPE){
				if (token->prev->type != WORD && token->prev->type != PRNTH_RIGHT)
					return (snytax_error_message(token->value));}
		else if (token->type == INPUT || token->type == OUTPUT_OVER || \
				token->type == HERE_DOC || token->type == OUTPUT_APPEND){
				if (token->prev->type == INPUT || token->prev->type == OUTPUT_OVER || \
				token->prev->type == HERE_DOC || token->prev->type == OUTPUT_APPEND)
					return (snytax_error_message(token->value));}
		else if (token->type == PRNTH_LEFT){
			if (token->prev->type != LOGICAL_AND && token->prev->type != LOGICAL_OR && \
				token->prev->type != PIPE && token->prev->type != PRNTH_LEFT)
				return (snytax_error_message(token->value));}
		else if (token->type == PRNTH_RIGHT){
			if (token->prev->type != WORD && token->prev->type != PRNTH_RIGHT)
				return (snytax_error_message(token->value));}
		else if (token->type == WORD){
			if (token->prev->type == PRNTH_RIGHT)
				return (snytax_error_message(token->value));}
		token = token->next;
	}
	return (1);
}