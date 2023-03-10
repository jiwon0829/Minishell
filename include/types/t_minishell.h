/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:25 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:45:09 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include <term.h>
# include "t_envp.h"
# include "t_cmd.h"
# include "t_redirect.h"
# include "t_heredoc.h"

typedef struct s_minishell	t_minishell;
typedef struct s_cmd_tbl	t_cmd_tbl;

struct s_minishell
{
	int			exit_status;
	int			exit_fdin;
	int			exit_fdout;
	int			heredoc_cnt;
	int			pipe_cnt;
	int			inchild;
	int			scmd_builtin;
	t_envp		*envp;
	t_cmd_tbl	*cmd_tbl;
	t_redirect	*redirect;
	t_heredoc	*heredoc;
};

#endif
