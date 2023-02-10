#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"

// void expender(t_minishell *minishell, t_parse_tree *parse_tree)
// {
// 	is_wildcard();//여기서 와일드카드처리
	
// }