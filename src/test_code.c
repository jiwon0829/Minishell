#include "test_code.h"

void print_envp_test(t_envp *envp)
{
    t_envp *tmp;

    tmp = envp;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void print_cmd_tbl(t_cmd_tbl *tbl)
{
    for (int i=0;i<tbl->cnt;i++)
    {
        printf("%s %s %d\n", tbl->cmd[i].cmd, tbl->cmd[i].opt, tbl->cmd[i].argc);
    }
}

void print_node(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s(%d)\t", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_lexer_token(t_token *token)
{
    t_token *test;
    test = token;
	while(test)
	{
		printf("(%s)",test->value);
        if (test->type == 2)
    		printf("type:PIPE -> ");
        else if (test->type == 3)
            printf("type:INPUT -> ");
        else if (test->type == 4)
    		printf("type:OUTPUT_OVER -> ");        
        else if (test->type == 5)
    		printf("type:HERE_DOC -> ");
        else if (test->type == 6)
            printf("type:OUTPUT_APPEND -> ");
        else if (test->type == 10)
    		printf("type:PRNTH_LEFT -> ");
        else if (test->type == 11)
    		printf("type:PRNTH_LEFT ");    
        else if (test->type == 12)
            printf("type:LOGIC_AND -> ");
        else if (test->type == 13)
    		printf("type:LOGIC_OR -> ");
		else
			printf("type:WORD ->");
		test = test->next;
	}
    printf("\n");
}

void print_tokenizer_token(t_token *token)
{
	t_token *test;
	test = token;
	while(test)
	{
		printf("(%s) -> ",test->value);
		test = test->next;
	}
	printf("\n");
}

void print_parse_tree(t_parse_tree *parse_tree, int level)
{
	printf("level%d root(%d)\t", level, parse_tree->type);
	print_node(parse_tree->token);
	if (parse_tree->left){printf("left>>");
		print_parse_tree(parse_tree->left, level + 1);}
	if (parse_tree->right){printf("right>>");
		print_parse_tree(parse_tree->right, level + 1);}
}

void print_redir_list(t_redirect *head)
{
		printf("-----cur redir_list----\n");
	while (head)
	{
		printf("(%d\t%d)\n", head->fd[0], head->fd[1]);
		head = head->next;
	}
	printf("----------\n--------");
}

