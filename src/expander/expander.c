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

static char	*expen_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcpy(&ptr[s1_len], s2, s2_len + 1);
	return (ptr);
}

void remove_dollor(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
{
	int	j;
	int	k;
	char	*first_str;
	char	*middle_str;
	char	*change_str;
	char	*last_str;
	char	*return_str;

	// printf("cur val:%s\n",parse_tree->token->value);
	(void)minishell;
	j = *i + 1; // j = 7
	first_str = ft_substr(parse_tree->token->value, 0, *i);
	// printf("first_str :%s\n", first_str);
	while (parse_tree->token->value[j])
	{
		if  (parse_tree->token->value[j] == '$'	|| parse_tree->token->value[j] == '\''
			|| parse_tree->token->value[j] == '"' || parse_tree->token->value[j] == ' ')
			break;
		j++; // j = 9
	}
	k = j;
	while (parse_tree->token->value[k])
		k++;
	middle_str = ft_substr(parse_tree->token->value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	change_str = get_envpNode(minishell->envp, middle_str)->value;
	// printf("change val :%s\n", change_str);
	return_str = expen_strjoin(first_str, change_str);
	*i = strlen(return_str) - 1;
	last_str = ft_substr(parse_tree->token->value, j, k - j + 1);
	// printf("last_str :%s\n", last_str);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);


	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(return_str, last_str);
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
	{
		j++; // j = 9
	}
	k = j + 1;
	while (parse_tree->token->value[k])
		k++;
	middle_str = ft_substr(parse_tree->token->value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	return_str = expen_strjoin(first_str, middle_str);
	*i = strlen(return_str);
	last_str = ft_substr(parse_tree->token->value, j + 1, k - j + 1);
	// printf("last_str :%s\n", last_str);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);


	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(return_str, last_str);

	// i + 1 ~ j - 1
}

void remove_dquotes(t_minishell *minishell, t_parse_tree *parse_tree, int *i)
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
	// printf("first_str :!%s!\n", first_str);
	while (parse_tree->token->value[j] != '"')
	{
		if (parse_tree->token->value[j] == '$')
				remove_dollor(minishell, parse_tree, &j);
		j++; // j = 9
	}
	k = j + 1;
	while (parse_tree->token->value[k])
		k++;
	middle_str = ft_substr(parse_tree->token->value, *i + 1, j - *i - 1);
	// printf("middle_str :!%s!\n", middle_str);
	return_str = expen_strjoin(first_str, middle_str);
	*i = strlen(return_str);
	last_str = ft_substr(parse_tree->token->value, j + 1, k - j + 1);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);

	free(parse_tree->token->value);
	parse_tree->token->value = expen_strjoin(return_str, last_str);

	// i + 1 ~ j - 1
}

void expander(t_minishell *minishell, t_parse_tree *parse_tree)
{
	// char	*new_str;
	int		i;
	// t_parse_tree	*tmp_parse_tree;
	t_token			*tmp_token;

	// tmp_parse_tree = parse_tree;
	// is_wildcard();//여기서 와일드카드처리
	// i = 0;
	// printf("remove dquote : %s\n", parse_tree->token->value);
	
	// printf("term val :%s\n",get_envpNode(minishell->envp, "USER")->value);
	// exit (0);
	tmp_token = parse_tree->token;
	while (parse_tree->token)
	{
		i = 0;
		while (parse_tree->token->value[i])
		{
			if (parse_tree->token->value[i] == '\'')
			{
				remove_squotes(minishell, parse_tree, &i);
				// printf("remove squote : %s\n", parse_tree->token->value);
			}
			if (parse_tree->token->value[i] == '"')
			{
				remove_dquotes(minishell, parse_tree, &i);
				// printf("remove dquote : %s\n", parse_tree->token->value);
			}
			else if (parse_tree->token->value[i] == '$')
			{
				remove_dollor(minishell, parse_tree, &i);
				// printf("remove dollor : %s\n", parse_tree->token->value);
			}
			if (!parse_tree->token->value[i])
				break;
			i = i + 1;
		}
			parse_tree->token = parse_tree->token->next;
	}
	parse_tree->token = tmp_token;
	// parse_tree = tmp_parse_tree;
				// exit (0);
}