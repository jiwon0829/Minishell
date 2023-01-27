#ifndef TEST_CODE_H
# define TEST_CODE_H

#include <stdio.h>
#include "minishell.h"
#include "envp.h"
#include "builtin.h"
#include "parser.h"

void print_envp_test(t_envp *envp);
void print_cmd_tbl(t_cmd_tbl *tbl);
void print_parse_tree(t_parse_tree *parse_tree, int level);

#endif