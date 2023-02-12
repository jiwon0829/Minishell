#include "minishell.h"
#include "exec.h"
#include "envp.h"
#include "t_cmd.h"
#include <stdio.h>
#include "lexer.h"
#include "t_parse_tree.h"
#include "t_heredoc.h"
#include "error_message.h"
#include "heredoc.h"
#include "expander.h"
#include "term_signal.h"

// static char	*expand_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ptr;
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(NULL));
// 	if (len > ft_strlen(s))
// 	{
// 		len = ft_strlen(s);
// 		ptr = (char *)malloc(sizeof(char) * (len - start + 1));
// 	}
// 	else
// 		ptr = (char *) malloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (0);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		ptr[i] = s[start + i];
// 		++i;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// static char	*expen_strjoin(char *s1, char *s2)
// {
// 	char	*ptr;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (!s1)
// 		return (s2);
// 	else if (!s2)
// 		return (s1);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (!ptr)
// 		return (0);
// 	ft_strlcpy(ptr, s1, s1_len + 1);
// 	ft_strlcpy(&ptr[s1_len], s2, s2_len + 1);
// 	return (ptr);
// }

int heredoc_remove_dollor(t_minishell *minishell, char **value, int *i)
{
	int ret;
	// int	i;
	int	j;
	int	k;
	int exit_flag;
	char	*first_str;
	char	*middle_str;
	char	*change_str;
	char	*last_str;
	char	*return_str;



	ret = 0;
	exit_flag = 0;
	// printf("cur val:%s\n",parse_tree->token->value);
	(void)minishell;
	j = *i + 1; // j = 7
	// printf("first_str :%s\n", first_str);
	while (value[0][j])
	{ 
		if (value[0][j] == '?')
		{
			heredoc_expand_exit_status(minishell, value, i, j);
			exit_flag = 1;
			break;
		}
		if  (value[0][j] == '$'	|| value[0][j] == '\''
			|| value[0][j] == '"' || value[0][j] == ' ')
			break;
		j++; // j = 9
	}
	if (exit_flag == 0)
	{
		first_str = expand_substr(*value, 0, *i);
		k = j;
		while (value[0][k])
			k++;
		middle_str = ft_substr(*value, *i + 1, j - *i - 1);
		// printf("middle_str :%s\n", middle_str);
		last_str = expand_substr(*value, j, k - j + 1);
		// printf("last_str :%s\n", last_str);

		free(*value);


		// printf("middle_str :%s\n", middle_str);
		if (get_envpNode(minishell->envp, middle_str))
		{
		// printf("ger_envpnode :%s\n", middle_str);

			change_str = get_envpNode(minishell->envp, middle_str)->value;
			return_str = expen_strjoin(first_str, change_str);
			*value = expen_strjoin(return_str, last_str);
			*i = strlen(return_str) - 1 ;
		}
		else
		{
			// printf("else :%s\n", middle_str);
			// last_str = ft_substr(value, j, k - j + 1);
			*value = expen_strjoin(first_str, last_str);
			if (!first_str)
				*i = 0;
			else
				*i = strlen(first_str);
			ret = 1;
			// *i = 0;
		}
	}
		return (ret);

}

void heredoc_remove_squotes(t_minishell *minishell, char **value, int *i)
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
	first_str = expand_substr(*value, 0, *i);
	// printf("first_str :%s\n", first_str);
	while (value[0][j] != '\'')
	{
		j++; // j = 9
	}
	k = j + 1;
	while (value[0][k])
		k++;
	middle_str = ft_substr(*value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	return_str = expen_strjoin(first_str, middle_str);
	*i = strlen(return_str) - 1;
	last_str = ft_substr(*value, j + 1, k - j + 1);
	// printf("last_str :%s\n", last_str);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);

	free(*value);
	*value = expen_strjoin(return_str, last_str);

	// i + 1 ~ j - 1
}

void heredoc_remove_dquotes(t_minishell *minishell, char **value, int *i)
{
	int		j;
	int		k;
	char	*first_str;
	char	*middle_str;
	char	*last_str;
	char	*return_str;

	// printf("cur val:%s\n",*value);

	// printf("cur val:%s\n",parse_tree->token->*value);
	(void)minishell;
	j = *i + 1; // j = 7
	first_str = ft_substr(*value, 0, *i);
	// printf("first_str :!%s!, i:%d\n", first_str, *i);
	while (value[0][j] != '"')
		j++; // j = 9
	// printf("DD j = %d\n",j);
	k = j + 1;
	while (value[0][k])
		k++;
	// printf("DD k = %d\n",k);

	middle_str = ft_substr(*value, *i + 1, j - *i - 1);
	// printf("middle_str :!%s!\n", middle_str);
	return_str = expen_strjoin(first_str, middle_str);
	*i = strlen(return_str) - 1;
	last_str = ft_substr(*value, j + 1, k - j + 1);
	// printf("last_str :!%s! i:!%d!\n", last_str, *i);
	free(*value);
	*value = expen_strjoin(return_str, last_str);
	// printf("tok-val :!%s! i:!%d!\n", *value, *i);
	// i + 1 ~ j - 1
}

char *heredoc_expander(t_minishell *minishell, t_heredoc *heredoc, char *value)
{
	int	i;
	
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			heredoc_remove_squotes(minishell, &value, &i);
			heredoc->quote_flag = 1;
			// printf("remove squote : %s\n", value);
		}
		else if (value[i] == '"')
		{
			heredoc_remove_dquotes(minishell, &value, &i);
			heredoc->quote_flag = 1;
			// printf("remove dquote : %s\n", value);
		}
		if (i >= 0 && !value[i])
			break;
		i = i + 1;
	}
	return (value);
}

void *heredoc_dollor_expander(t_minishell *minishell, t_heredoc *heredoc, char **value)
{
	int i;

	(void)heredoc;
	i = 0;
		while (value[0][i])
		{
			if (value[0][i] == '$')
			{
				if (heredoc_remove_dollor(minishell, value, &i) == 1)
					i--;
				// printf("remove dollor : %s\n", *value);
			}
			if (i >= 0 && !value[0][i])
				break;
			i = i + 1;
		}
	return (*value);
}