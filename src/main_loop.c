#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (0);
	while (i < ft_strlen(s1))
	{
		ptr[i] = ((char *)s1)[i];
		++i;
	}
	ptr[i] = 0;
	return (ptr);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
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

static char *read_line(char **line)
{
	*line = readline("minishell$ ");
	return (*line);
}

void main_loop(t_minishell *minishell)
{
	char	*line;
	t_token	*token;

	while (read_line(&line))
	{
		add_history(&line);
		// check_line(&line);
		// token = lexer(minishell, line);
		token = lexer(line);
		// token = token->next;
		// token = token->next;

		while (0)
		{
			printf("11\n");
			// char *str;
			// printf("22\n");
			// str = ft_substr(token->tok,0, 1);
			// printf("len = %d ", token->len);
			// printf("str = %s ", token->tok);			
			// printf("type : %d, value :%s\n",token->type, str);
			// printf("33\n");			
			// token = token->next;
			// free (str);
		}
			printf("\n");			

	}
}


// cc -lreadline -L/Users/song-in-oh/goinfre/.brew/readline/lib -I $HOME/goinfre/.brew/readline/include minishell.c lexer/lexer.c lexer/lexer_free.c lexer/lexer_util.c lexer/token.c main_loop.c