/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:16:26 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 18:17:15 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	check_quot(char input)
{
	if (input == '\'')
		return (SQUOT);
	else if (input == '\"')
		return (DQUOT);
	return (0);
}
