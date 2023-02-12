#include "exec.h"
#include "lexer.h"
#include "parser.h"
#include <dirent.h>
#include "test_code.h"

static int is_valid_value(char *dname, char *str)
{

	int dname_len;
	int str_len;
	int i;
	int d_i;

	dname_len = ft_strlen(dname);
	str_len = ft_strlen(str);
	i = 0;
	while (i < dname_len && i < str_len && (dname[i] == str[i]))
		++i;
	if (str_len == i)	//str=k, dname=k -> return (TRUE)
		return(dname_len == i);
	if (str[i] == '*')
	{
		d_i = 0;
		while (i + d_i <= dname_len)
		{
			//if (is_valid_value(str + 1 + i, dname + d_i + i))
			if (is_valid_value(dname + d_i + i, str + 1 + i))
				return (1);
			++d_i;
		}
	}
	return (0);
}

static int add_wildcard_token(t_token *token, char *dname, int *cnt)
{
	char *str;
	t_token *new;

	if (!(*cnt))
	{
		str = ft_strdup(dname);
		if (!str)
			return (0);
		free(token->value);token->value = NULL;
		token->value = str;
	}
	else
	{
		new = create_token(ft_strlen(dname), dname, WORD);
		new->prev = token->prev;
		token->prev->next = new;
		new->next = token;
		token->prev = new;
		if (!new)
			return (0);
	}
	(*cnt)++;
	return (1);

}

/*static void re_wildcard(char *str)
{
	while (*str)
	{
		if (*str == '*')
			*str *= -1;
		++str;
	}
}*/

static int is_valid_wildcard(t_token *token, char *str)
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
		if (is_valid_value(dirent->d_name, str) && !(add_wildcard_token(token, dirent->d_name, &cnt)))
		{
			closedir(dir);
			return (0);
		}
	}
	//if (!cnt)
	//	re_wildcard(token->value);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}

static char *set_wildcard(char *value)
{
	char *ret;
	int ret_len;
	int i=0;
	char *tmp;

	tmp = ft_strdup(value);
	ret_len = 0;
	while (value[i])
	{
		if (i == 0)
			ret_len++;
		else if (value[i] != '*' || (value[i] == '*' && tmp[ret_len - 1] != '*'))
		{
			tmp[ret_len] = value[i];
			ret_len++;
		}
		++i;
	}
	tmp[ret_len] = '\0';
	ret = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (ret);
}

void    is_wildcard(t_token *token)
{
	char *str;

	if (!token)
		return ;
	str = NULL;
	while (token)
	{
		if (token->type == WORD && ft_strchr(token->value, '*'))
		{
			str = set_wildcard(token->value);
			if (!str || !is_valid_wildcard(token, str))
			{
				free(str);
				return ;
			}
			free(str);
			str = NULL;
		}
		token = token->next;
	}
}