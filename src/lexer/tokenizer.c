/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:21:24 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/20 15:49:10 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "test_code.h"

void	sub_lexer(int *type, char *input_i, char **start, t_token **tokens)
{
	if (*type == WORD && get_type(*input_i) != WORD)
		init_common_token(tokens, input_i, start, type);
	else if (*type == PRNTH_LEFT)
		init_common_token(tokens, input_i, start, type);
	else if (*type == PRNTH_RIGHT)
		init_common_token(tokens, input_i, start, type);
}

int	sub_lexer_quotes(int *type, char *input_i, \
					char **start, t_token **tokens)
{
	int	ret;

	ret = 0;
	if (check_quot(*input_i) == DQUOT || check_quot(*input_i) == SQUOT)
		ret = init_quot_token(tokens, input_i, start, type);
	return (ret);
}

t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	int		i;
	int		type;
	int		temp;
	char	*start;

	if (!ft_strlen(input))
		return (NULL);
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	start = input;
	while (input[i])
	{
		sub_lexer(&type, &input[i], &start, &tokens);
		temp = sub_lexer_quotes(&type, &input[i], &start, &tokens);
		i += temp;
		temp = tokenize_special(&type, &input[i], &start, &tokens);
		i += temp + 1;
	}
	add_token(&tokens, create_token((int)(&input[i] - start), start, type));
	return (tokens);
}
