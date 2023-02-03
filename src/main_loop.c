#include "minishell.h"
#include "signal.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "test_code.h"

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
	int i = -1;
	size_t blank_cnt = 0;
	char quote = check_quote(*line);

	if (ft_strlen(*line) == 0)
		return (0);
	while ((*line)[++i])
	{
		if ((*line)[i] == ' ')
			++blank_cnt;
	}
	if (blank_cnt == ft_strlen(*line) || quote)
		return (0);
	return (1);
}

void main_loop(t_minishell *minishell)
{
	char			*line;
	t_token			*token;
	t_parse_tree	*parse_tree;

	while (read_line(&line))
	{
		add_history(line);
		if (!check_line(&line))
			continue ;
		token = tokenizer(line);
		free(line);line = NULL;
		token = lexer(token);
		parse_tree = parser(token);
		// printf("%s %s\n",parse_tree->token->value,parse_tree->token->next->value);
		if (parse_tree)print_parse_tree(parse_tree, 0);
			//executor(minishell, parse_tree);
		// print_parse_tree(parse_tree, 0);
		/*free(parse_tree);
		parse_tree = NULL;
		free(token); token = NULL;*/
	}(void)minishell;
	rl_clear_history();
	return ;
}