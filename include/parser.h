#ifndef PARSER_H
# define PARSER_H

#include <stdlib.h>
#include "types/t_parse_tree.h"
#include "lexer.h"
#define FALSE 0
#define TRUE 1

t_parse_tree *parser(t_minishell *minishell, t_token *token);

//tool
t_token *get_head_token(t_token *token);
t_token *get_tail_token(t_token *token);
void	set_left_token(t_token *token, t_token *find);
void	set_left_token_redirection(t_parse_tree *parse_tree, t_token *token);
//make_tree
void parse_token(t_parse_tree **parse_tree, t_token **tail, t_parse_tree *prev_tree);
int  find_head_from_tail(t_token *tail, t_token **find, int type);
int  find_head_from_head(t_token *head, t_token **find, int type);
void go_left_node(t_parse_tree **parse_tree);
void go_right_node(t_parse_tree **parse_tree);

//insert_tree
t_parse_tree *init_parse_tree(void);
void set_new_node(t_parse_tree *new_node, t_parse_tree *prev_tree, t_token *find);
void get_left_node(t_parse_tree *parse_tree, t_token *token);
void	get_right_node(t_parse_tree *parse_tree, t_token *token);
void	insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree);

//parenthesis
int  matching_parenthesis(t_token *token);
void    remove_tail_token(t_token **tail);
void    remove_token(t_token **del_token);
void    check_parenthesis(t_parse_tree **parse_tree, t_token **tail);

//check_syntax
int syntax_error_check(t_token *token);
int first_token_error(t_token *token);
int context_token_error(t_token *token);
int last_token_error(t_token *token);
int parenthesis_match_error(t_token *token);;

//utils
int	is_redir(int type);
int	is_logical(int type);
int	is_valid_prev_prnth_left(int type);
char	*tokentostring(t_token *token);
#endif 