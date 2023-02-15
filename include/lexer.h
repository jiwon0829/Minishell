#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"
#include "types/t_token.h"

# define WORD 0
# define BLANK 1
# define PIPE 2
# define INPUT 3
# define OUTPUT_OVER 4
# define HERE_DOC 5
# define OUTPUT_APPEND 6
# define DQUOT 7
# define SQUOT 8
# define PRNTH_LEFT 10
# define PRNTH_RIGHT 11
# define LOGICAL_AND 12
# define LOGICAL_OR 13
# define SEPAR_MORE 14
# define SEPAR_LESS 15
# define SEPAR_PIPE 16
# define LOGICAL 17
# define REDIR 18

//lexer.c
// t_token	*lexer(t_minishell *minishell, char *input);
t_token	*tokenizer(char *input);
int	sub_lexer_quotes(int *type, char *input_i, char **start, t_token **tokens);
void	sub_lexer(int *type, char *input_i, char **start, t_token **tokens);


//lexer_util.c
void    init_common_token(t_token **token, char *input, char **start, int *type);
int 	init_quot_token(t_token **token, char *input, char **start, int *type);
int     get_type(char input);
void	init_index(int *index);
void	init_separs(char **separs);

//lexer_check_qoute.c
int check_quot(char input);

//lexer_free.c
t_token *free_tokens(t_token *token);

//lexer.c
t_token *lexer(t_token *token);
void tokenize_space(int *type, char *input_i, char **start);
int	set_token_types(t_token **token);
int	sub_set_token_types(char **separs, int *index, t_token *temp);


//tokenize_symbol.c
int	tokenize_special(int *type, char *input_i, char **start, t_token **tokens);

//token.c
void	add_token(t_token **first, t_token *to_add);
t_token	*create_token(int length, char *start, int type);
void	insert_token(t_token **tail, t_token *to_add);
void	del_token(t_token **target);
#endif