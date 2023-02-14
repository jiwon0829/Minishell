/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:27:57 by inosong           #+#    #+#             */
/*   Updated: 2023/02/13 11:31:43 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_expander(t_expander *expander)
{
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

void	expand_dollor(t_minishell *minishell, t_expander *ex,
	t_parse_tree *parse_tree, int *i)
{
	ex->first_str = expand_substr(parse_tree->token->value, 0, *i);
	ex->k = ex->j;
	while (parse_tree->token->value[ex->k])
		ex->k++;
	ex->middle_str = ft_substr(parse_tree->token->value,
			*i + 1, ex->j - *i - 1);
	ex->last_str = expand_substr(parse_tree->token->value,
			ex->j, ex->k - ex->j + 1);
	free(parse_tree->token->value);
	if (get_envpNode(minishell->envp, ex->middle_str))
	{
		ex->change_str = get_envpNode(minishell->envp, ex->middle_str)->value;
		ex->return_str = expen_strjoin(ex->first_str, ex->change_str);
		parse_tree->token->value = expen_strjoin(ex->return_str, ex->last_str);
		*i = strlen(ex->return_str) - 1 ;
	}
	else
	{
		parse_tree->token->value = expen_strjoin(ex->first_str, ex->last_str);
		if (!(ex->first_str))
			*i = 0;
		else
			*i = strlen(ex->first_str);
		ex->ret = 1;
	}
}

void	expand_exit_status(t_minishell *minishell, t_parse_tree *parse_tree,
	int *i, int j)
{
	int		k;
	char	*first_str;
	char	*last_str;
	char	*change_str;
	char	*return_str;

	first_str = expand_substr(parse_tree->token->value, 0, *i);
	k = j;
	while (parse_tree->token->value[k])
		k++;
	last_str = expand_substr(parse_tree->token->value, j + 1, k - j + 1);
	free(parse_tree->token->value);
	change_str = ft_itoa(minishell->exit_status);
	return_str = expen_strjoin(first_str, change_str);
	parse_tree->token->value = expen_strjoin(return_str, last_str);
	*i = strlen(return_str) - 1;
}
