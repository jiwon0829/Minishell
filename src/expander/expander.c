#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "expander.h"
#include "t_expander.h"

static void	is_split_token(t_parse_tree *parse_tree, int start, int *end)
{
	char *tmp = ft_substr(parse_tree->token->value, start, *end - start + 1);
	
	if (!tmp)
		return ;
	if (ft_strchr(tmp, ' '))
	{
		char **arr;
		arr = ft_split(tmp, ' ');
		int k = 0;
		while (arr[k])
		{
			insert_token(&parse_tree->token, create_token(ft_strlen(arr[k]), arr[k], WORD));
			k++;
		}
	}
	del_token(&(parse_tree->token));
	*end = 0;
}

int remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, int *i, int check)
{
	t_expander expander;int init = *i;

	init_expander(&expander);
	(void)minishell;
	expander.j = *i + 1; // j = 7
	// printf("first_str :%s\n", first_str);
	while (parse_tree->token->value[expander.j])
	{ 
		if (parse_tree->token->value[expander.j] == '?')
		{
			expand_exit_status(minishell, parse_tree, i, expander.j);
			expander.exit_flag = 1;
			break;
		}
		if  (parse_tree->token->value[expander.j] == '$'	|| parse_tree->token->value[expander.j] == '\''
			|| parse_tree->token->value[expander.j] == '"' || parse_tree->token->value[expander.j] == ' ')
			break;
		expander.j++; // expander.j = 9
	}
	if (expander.exit_flag == 0)
	{
		expand_dollor(minishell, &expander, parse_tree, i);
	}
	if (check)
		is_split_token(parse_tree, init, i);
	return (expander.ret);

}

void remove_squotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
{
	int j;
	int	k;
	char	*first_str;
	char	*middle_str;
	char	*last_str;
	char	*return_str;

	// printf("cur val:%s\n",parse_tree->token->value);
	(void)minishell;
	j = *i + 1; // j = 7
	first_str = ft_substr(parse_tree->token->value, 0, *i);
	// printf("first_str :%s\n", first_str);
	while (parse_tree->token->value[j] != '\'')
		j++; // j = 9
	k = j + 1;
	while (parse_tree->token->value[k])
		k++;
	middle_str = ft_substr(parse_tree->token->value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	return_str = expen_strjoin(first_str, middle_str);
	*i = strlen(return_str) - 1;
	last_str = ft_substr(parse_tree->token->value, j + 1, k - j + 1);
	// printf("last_str :%s\n", last_str);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);
	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(return_str, last_str);
	// i + 1 ~ j - 1
}

void remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
{
	t_expander expander;

	init_expander(&expander);
	// printf("cur val:%s\n",parse_tree->token->value);
	(void)minishell;
	expander.j = *i + 1; // j = 7
	expander.first_str = ft_substr(parse_tree->token->value, 0, *i);
	// printf("first_str :!%s!, i:%d\n", first_str, *i);
	while (parse_tree->token->value[expander.j] != '"')
	{
		if (parse_tree->token->value[expander.j] == '$')
		{
				if (remove_dollor(minishell, parse_tree, &(expander.j), 0) == 1)
					expander.j--;
		}
		expander.j++; // j = 9
	}
	// printf("DD j = %d\n",j);
	expander.k = expander.j + 1;
	while (parse_tree->token->value[expander.k])
		expander.k++;
	// printf("DD k = %d\n",k);

	expander.middle_str = ft_substr(parse_tree->token->value, *i + 1, expander.j - *i - 1);
	// printf("middle_str :!%s!\n", middle_str);
	expander.return_str = expen_strjoin(expander.first_str, expander.middle_str);
	*i = strlen(expander.return_str) - 1;
	expander.last_str = ft_substr(parse_tree->token->value, expander.j + 1, expander.k - expander.j + 1);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);

	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(expander.return_str, expander.last_str);
	// printf("tok-val :!%s! i:!%d!\n", parse_tree->token->value, *i);
	// i + 1 ~ j - 1
}
#include "test_code.h"
void expander(t_minishell *minishell, t_parse_tree *parse_tree)
{
	t_token	*tmp_token;
	int		i;
	if (parse_tree->type == WORD)
		is_wildcard(parse_tree->token);//여기서 와일드카드처리
	tmp_token = parse_tree->token;
	while (parse_tree->token)
	{
		i = 0;
		while (parse_tree->token->value[i])
		{
			if (parse_tree->token->value[i] == '$')
			{
				remove_dollor(minishell, parse_tree, &i, 1);
				if (!parse_tree->token)
					break;
			}
				// printf("remove dollor : %s\n", parse_tree->token->value);
			if (parse_tree->token->value[i] == '\'')
				remove_squotes(minishell, parse_tree, &i);
				// printf("remove squote : %s\n", parse_tree->token->value);
			else if (parse_tree->token->value[i] == '"')
				remove_dquotes(minishell, parse_tree, &i);
				// printf("remove dquote : %s\n", parse_tree->token->value);
			if (i >= 0 && !parse_tree->token->value[i])
				break;
			i = i + 1;
		}
		if (parse_tree->token)
			parse_tree->token = parse_tree->token->next;
	}
	parse_tree->token = tmp_token;
}