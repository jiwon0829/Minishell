#include "minishell.h"
#include "lexer.h"

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


static char	check_quote(char *line)
{
	int	i = -1;
	char quote = 0;

	if (!line)
		return (0);
	while (line[++i])
	{
		if ((line[i] == '\\' && ((int)(ft_strlen(line)) - 1 != i + 1) && line[i + 1] == '\'') || \
			(line[i] == '\\' && ((int)(ft_strlen(line)) - 1 != i + 1) && line[i + 1] == '\"'))
		{
			++i;
			continue ;
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == '\'' && line[i] == '\'')
				quote = 0;
			else if (quote == '"' && line[i] == '"')
				quote = 0;
			else if (quote == '\'' && line[i] == '"')
				continue ;
			else if (quote == '"' && line[i] == '\'')
				continue ;
		}
	}
	return (quote);
}

static int check_line(char **line)
{
	//TODO NULL string, empty string
	if (ft_strlen(*line) == 0)
		return (0);

	//TODO blank string
	int i = -1;
	size_t blank_cnt = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == ' ')
			++blank_cnt;
	}
	if (blank_cnt == ft_strlen(*line))
		return (0);
	//TODO unclosed quotes
	char quote = check_quote(*line);
	while (quote)
	{
		*line = ft_strjoin(*line, "\n");
		*line = ft_strjoin(*line, readline("> "));
		quote = check_quote(*line);
	}
	return (1);
}

void main_loop(t_minishell *minishell)
{
	char			*line;
	t_token			*token;
	
	while (read_line(&line))
	{
		add_history(line);
		check_line(&line);
        printf("input:%s\n", line);
		token = lexer(line);
        //analize_line
		free(line);
		//parser
        //exev
	}(void)minishell;(void)token;
	return ;
	// cc -lreadline -L/Users/song-in-oh/goinfre/.brew/readline/lib -I $HOME/goinfre/.brew/readline/include minishell.c lexer/lexer.c lexer/lexer_free.c lexer/lexer_util.c lexer/token.c main_loop.c
}

