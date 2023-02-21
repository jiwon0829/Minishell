/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:18:13 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:44:25 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXEC_H
# define T_EXEC_H

# include "t_parse_tree.h"
# include "t_token.h"
# include "lexer.h"

typedef struct s_pipe	t_pipe;

struct s_pipe
{
	int				fd[2];
	struct s_pipe	*next;
	struct s_pipe	*prev;
	int				left_flag;
	int				right_flag;
	int				type;
	int				pid;
	int				fdin;
	int				fdout;
};

#endif
