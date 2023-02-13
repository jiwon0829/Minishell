/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:50:03 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 14:21:29 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "test_code.h"

static char	*read_line(char **line)
{
	*line = readline("minishell$ ");
	return (*line);
}

static char	check_quote(char *line)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if ((line[i] == '\\' && ((int)(ft_strlen(line)) - 1 != i + 1) \
		&& line[i + 1] == '\'') || (line[i] == '\\' && \
		((int)(ft_strlen(line)) - 1 != i + 1) && line[i + 1] == '\"'))
		{
			++i;
			continue ;
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if ((quote == '\'' && line[i] == '\'') || \
			(quote == '"' && line[i] == '"'))
				quote = 0;
		}
	}
	return (quote);
}

static int	check_line(char **line)
{
	int		i;
	size_t	blank_cnt ;
	char	quote;

	i = -1;
	blank_cnt = 0;
	if (ft_strlen(*line) == 0)
		return (0);
	quote = check_quote(*line);
	while ((*line)[++i])
	{
		if ((*line)[i] == ' ')
			++blank_cnt;
	}
	if (blank_cnt == ft_strlen(*line) || quote)
		return (0);
	return (1);
}

void	main_loop(t_minishell *minishell)
{
	char			*line;
	char			*exit_str[2];
	t_token			*token;
	t_parse_tree	*parse_tree;

	while (read_line(&line))
	{
		add_history(line);
		if (!check_line(&line))
		{
			free(line);
			continue ;
		}
		token = tokenizer(line);
		free(line);
		line = NULL;
		token = lexer(token);
		parse_tree = parser(token);
		if (parse_tree)
			executor(minishell, parse_tree);
	}
	rl_clear_history();
	exit_str[0] =  ft_strdup("exit");
	exit_str[1] = 0;
	ft_exit(minishell, exit_str);
	return ;
}
