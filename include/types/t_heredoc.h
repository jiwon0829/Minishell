/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:44:58 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:44:59 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HEREDOC_H
# define T_HEREDOC_H

# include "t_parse_tree.h"
# include "t_token.h"

typedef struct s_heredoc	t_heredoc;

struct s_heredoc
{
	int			fd[2];
	int			pid;
	int			quote_flag;
	char		*limit;
	t_heredoc	*next;
};

#endif