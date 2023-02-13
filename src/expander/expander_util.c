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

void init_expander(t_expander *expander)
{
	// expander = (t_expander *)malloc(sizeof(expander));
	expander->ret = 0;
	expander->j = 0;
	expander->k = 0;
	expander->exit_flag = 0;
	expander->first_str = NULL;
	expander->middle_str = NULL;
	expander->change_str = NULL;
	expander->last_str = NULL;
	expander->return_str = NULL;
}

char	*expand_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(NULL));
	if (len > ft_strlen(s))
	{
		len = ft_strlen(s);
		ptr = (char *)malloc(sizeof(char) * (len - start + 1));
	}
	else
		ptr = (char *) malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*expen_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcpy(&ptr[s1_len], s2, s2_len + 1);
	return (ptr);
}

void expand_dollor(t_minishell *minishell, t_expander *expander, t_parse_tree *parse_tree, int *i)
{
	expander->first_str = expand_substr(parse_tree->token->value, 0, *i);
	expander->k = expander->j;
	while (parse_tree->token->value[expander->k])
		expander->k++;
	expander->middle_str = ft_substr(parse_tree->token->value, *i + 1, expander->j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	expander->last_str = expand_substr(parse_tree->token->value, expander->j, expander->k - expander->j + 1);
	// printf("last_str :%s\n", last_str);
	free(parse_tree->token->value);
	// printf("middle_str :%s\n", middle_str);
	if (get_envpnode(minishell->envp, expander->middle_str))
	{
	// printf("ger_envpnode :%s\n", middle_str);
		expander->change_str = get_envpnode(minishell->envp, expander->middle_str)->value;
		expander->return_str = expen_strjoin(expander->first_str, expander->change_str);
		parse_tree->token->value = expen_strjoin(expander->return_str, expander->last_str);
		*i = strlen(expander->return_str) - 1 ;
	}
	else
	{
		// printf("else :%s\n", middle_str);
		// last_str = ft_substr(parse_tree->token->value, j, k - j + 1);
		parse_tree->token->value = expen_strjoin(expander->first_str, expander->last_str);
		if (!(expander->first_str))
			*i = 0;
		else
			*i = strlen(expander->first_str);
		expander->ret = 1;
		// *i = 0;
	}
}
void expand_exit_status(t_minishell *minishell, t_parse_tree *parse_tree, int *i, int j)
{
	int k;
	char *first_str;
	// char *middle_str;
	char *last_str;
	char *change_str;
	char *return_str;

	first_str = expand_substr(parse_tree->token->value, 0, *i);
	k = j;
	while (parse_tree->token->value[k])
		k++;
	// middle_str = ft_substr(parse_tree->token->value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	last_str = expand_substr(parse_tree->token->value, j + 1, k - j + 1);
	// printf("last_str :%s\n", last_str);
	free(parse_tree->token->value);
	// printf("middle_str :%s\n", middle_str);
	change_str = ft_itoa(minishell->exit_status); //free
	return_str = expen_strjoin(first_str, change_str);
	parse_tree->token->value = expen_strjoin(return_str, last_str);
	*i = strlen(return_str) - 1;
}