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

// char	*expand_substr(char const *s, unsigned int start, size_t len)
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

// char	*expen_strjoin(char *s1, char *s2)
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

void heredoc_expand_exit_status(t_minishell *minishell, char **value, int *i, int j)
{
	int k;
	char *first_str;
	char *last_str;
	char *change_str;
	char *return_str;
	// char *middle_str;

	first_str = expand_substr(*value, 0, *i);
	k = j;
	while (value[0][k])
		k++;
	// middle_str = ft_substr(value, *i + 1, j - *i - 1);
	// printf("middle_str :%s\n", middle_str);
	last_str = expand_substr(*value, j + 1, k - j + 1);
	// printf("last_str :%s\n", last_str);

	free(*value);

	change_str = ft_itoa(minishell->exit_status); //free
	return_str = expen_strjoin(first_str, change_str);
	*value = expen_strjoin(return_str, last_str);
	*i = strlen(return_str) - 1 ;
}