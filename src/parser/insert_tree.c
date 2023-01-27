#include "parser.h"

t_parse_tree *init_parse_tree(void)
{
	t_parse_tree *ret;

	ret = (t_parse_tree *)malloc(sizeof(t_parse_tree));
	ft_memset(ret, 0, sizeof(t_parse_tree));
	ret->type = WORD;
	return (ret);
}

void set_new_node(t_parse_tree *new_node, t_parse_tree *prev_tree, t_token *find)
{
	new_node->up = prev_tree;
	new_node->token = find;
	new_node->type = find->type;
}

void	set_left_token(t_token *token, t_token *find)
{
	if (!token)
		return ;
	while (token && (token->next != find))
		token = token->next;
	if (token)
		token->next = NULL;
}

void	set_left_token_redirection(t_parse_tree *parse_tree, t_token *token)
{
	t_token	*left_tail;

	left_tail = get_tail_token(parse_tree->token);
	if (token->next->next)
	{
		if (left_tail)
		{
			left_tail->next = token->next->next;
			left_tail->next->prev = left_tail;
		}
		else
		{
			parse_tree->token = token->next->next;
			parse_tree->token->prev = NULL;
		}
		token->next->next = NULL;
	}
}

char	*tokentostring(t_token *token)
{
	char	*ret;
	t_token	*tmp;

	ret = malloc(1);
	tmp = token;
	while (tmp)
	{
		ret = ft_strjoin(ret, tmp->value);
		tmp = tmp->next;
	}
	return (ret);
}

void get_left_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->left = init_parse_tree();
	parse_tree->left->up = parse_tree;
	parse_tree->left->token = get_head_token(token);
	if (parse_tree->left->token == token)	//token's prev == NULL
		parse_tree->left->token = NULL;
	parse_tree->left->type = WORD;
	set_left_token(parse_tree->left->token, token);	//left->token의 이후 연결 끊기
	token->prev = NULL;	//사용한 token 연결 끊기
	if (token->type == INPUT || token->type == OUTPUT_OVER || token->type ==  HERE_DOC || token->type == OUTPUT_APPEND)
		set_left_token_redirection(parse_tree->left, token);
}

void	get_right_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->right = init_parse_tree();
	parse_tree->right->up = parse_tree;
	parse_tree->right->token = token->next;
	parse_tree->right->token->prev = NULL;
	parse_tree->right->type = WORD;
	token->next = NULL;
	if (token->type == INPUT || token->type == OUTPUT_OVER || token->type ==  HERE_DOC || token->type == OUTPUT_APPEND)
		parse_tree->right->token->next = NULL;
}

void	insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree)
{
	t_parse_tree    *new_tree;

	new_tree = init_parse_tree();   //new command 노드 만들어주기
	set_new_node(new_tree, prev_tree, find);    //new node에 이전 parse tree에 연결
	//new node의 left, right node 생성
	get_left_node(new_tree, find);
	get_right_node(new_tree, find);
	//parse tree를 new_node까지 반영하기
	if (parse_tree && *parse_tree)
	{
		free(*parse_tree);
		*parse_tree = NULL;
	}
	*parse_tree = new_tree;
}
