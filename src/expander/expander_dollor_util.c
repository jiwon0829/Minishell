/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollor_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:46:34 by inosong           #+#    #+#             */
/*   Updated: 2023/02/16 18:24:43 by hanjiwon         ###   ########.fr       */
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

// static add_cur_back_token(t_token **tail, t_token *to_add)
// {

// 	if (!to_add)
// 		return ;
// 	if (!(*tail)->prev)
// 	{
// 		(*tail)->prev = to_add;
// 		to_add->next = (*tail);
// 		return ;
// 	}
// 	(*tail)->prev->next = to_add;
// 	to_add->prev = (*tail)->prev;
// 	(*tail)->prev = to_add;
// 	to_add->next = (*tail);
// }
// }

// static void split_n_make_token(int link, int start,
// 	t_parse_tree *parse_tree, char *tmp)
// {
// 	char	**arr;
// 	t_token *tmp;
// 	int		k;

// 	k = 0;
// 	arr = ft_split(tmp, ' ');
// 	tmp = parse_tree->token;
// 	parse_tree->token = create_token(ft_strlen(arr[k]), arr[k], WORD);
// 	k++;
// 	while (arr[k])
// 	{
// 		add_cur_back_token(parse_tree->token,create_token(ft_strlen(arr[k]),
// 				arr[k], WORD));
// 		free(arr[k]);
// 		k++;
// 	}
// 	// while (arr[k])
// 	// {
// 	// 	if (k == 0 && start && link && parse_tree->token->value[start])
// 	// 		arr[k] = ft_strjoin(ft_substr(parse_tree->token->value, \
// 	// 			0, start), arr[k]);
// 	// 			{
// 	// 			insert_token(&parse_tree->token, create_token(ft_strlen(arr[k]),
// 	// 			arr[k], WORD));
// 	// 			printf("token : %s\n",parse_tree->token->value);
// 	// 			}
// 	// free(arr[k]);
// 	// 	k++;
// 	// }
// 	free(arr);
// }

// void	is_split_token(t_parse_tree *parse_tree, int start, int *end)
// {
// 	char	*tmp;
// 	int		link;
// 	//int		k;

// 	tmp = ft_substr(parse_tree->token->value, start, *end - start + 1);
// 	printf("tmp : %s\n",tmp);
// 	link = 1;
// 	//k = 0;
// 	if (!tmp)
// 		return ;
// 	if (tmp[0] == ' ')
// 		link = 0;
// 	if (ft_strchr(tmp, ' '))
// 		split_n_make_token(link, start, parse_tree, tmp);
// 	if (parse_tree->token->value[*end + 1] == 0)
// 	{
// 		del_token(&(parse_tree->token));
// 		*end = 0;
// 	}
// 	free(tmp);
// }
