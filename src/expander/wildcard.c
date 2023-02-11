#include "exec.h"
#include "lexer.h"
#include "parser.h"
#include <dirent.h>

static int is_valid_value(char *dname, char *str)
{

	int dname_len;
	int str_len;
	int i;
	int d_i;

	dname_len = ft_strlen(dname);
	str_len = ft_strlen(str);
	i = 0;
	while (i < dname_len && i < dname_len && (dname[i] == str[i]))
		++i;
	if (str_len == i)	//str=k, dname=k -> return (TRUE)
		return(dname_len == i);
	if (str[i] == '*')
	{
		d_i = 0;
		while (i + d_i <= dname_len)
		{
			if (is_valid_value(str + 1 + i, dname + d_i + i))
				return (1);
			++d_i;
		}
	}
	return (0);
}

static t_parse_tree	*link_tree(t_parse_tree *node, t_token *new)
{
	t_parse_tree *ret;

	ret = init_parse_tree();
	ret->token = new;
	if (!ret)
		return (NULL);
	ret->left = node->left;
	if (node->left)
		node->left->up = ret;
	if (node)
		node->left = ret;
	ret->up = node;
	return (ret);
}

static int add_wildcard_tree(t_parse_tree **parse_tree, t_token *token, char *dname, int *cnt)
{
	char *str;
	t_token *new;

	if (!(*cnt))
	{
		str = ft_strdup(dname);
		if (!str)
			return (0);
		free(token->value);
		token->value = str;
	}
	else
	{
		new = create_token(ft_strlen(dname), dname, WORD);
		if (!new)
			return (0);
		*parse_tree = link_tree(*parse_tree, new);
		if (!(*parse_tree))
			return (0);
	}
	(*cnt)++;
	return (1);

}

static void re_wildcard(char *str)
{
	while (*str)
	{
		if (*str == '*')
			*str *= -1;
		++str;
	}
}

static int is_valid_wildcard(t_parse_tree *parse_tree, t_token *token, char *str)
{
	DIR	*dir;
	struct dirent *dirent;
	int	cnt;

	cnt = 0;
	dir = opendir(".");	//지정한 디렉토리 열기(파일처럼 연다.)즉, 특정 디렉토리 안에 있는 파일과 디렉토리 검색을 위해 사용
	if (!dir)
		return (0);
	while ((dirent = readdir(dir)))	//디렉토리의 처음부터 파일 또는 디렉토리명을 순서대로 한 개씩 읽는다
	{
		if (is_valid_value(dirent->d_name, str) && !add_wildcard_tree(&parse_tree, token, dirent->d_name, &cnt))
		{
			closedir(dir);
			return (0);
		}
	}
	if (!cnt)
		re_wildcard(token->value);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}

void    is_wildcard(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token *token;
	char *str;

	if (!parse_tree || minishell->exit_status == 1)
		return ;
	token = parse_tree->token;
	while (token)
	{
		if (token->type == WORD && ft_strchr(token->value, '*'))
		{
			str = ft_strdup(token->value);
			if (!str || !is_valid_wildcard(parse_tree, token, str))
			{
				free(str);
				minishell->exit_status = 1;
				return ;
			}
			free(str);
			str = NULL;
		}
		token = token->next;
	}
	free(token);
	if (parse_tree->left)
		is_wildcard(minishell, parse_tree->left);
	if (parse_tree->right)
		is_wildcard(minishell, parse_tree->right);
}