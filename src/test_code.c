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

void print_parse_tree(t_parse_tree *parse_tree, int level)
{
	printf("level%d root(%d)\t", level, parse_tree->type);
	print_node(parse_tree->token);
	if (parse_tree->left)
		print_parse_tree(parse_tree->left, level + 1);
	if (parse_tree->right)
		print_parse_tree(parse_tree->right, level + 1);
}