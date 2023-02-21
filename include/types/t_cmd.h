/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:25:26 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:39:50 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CMD_H
# define T_CMD_H

# include <stdlib.h>
# include "t_minishell.h"
# include "../libft/libft.h"

typedef struct s_minishell	t_minishell;
typedef struct s_cmd_tbl	t_cmd_tbl;
typedef struct s_cmd		t_cmd;

struct s_cmd_tbl
{
	int		cnt;
	t_cmd	*cmd;
};

struct s_cmd
{
	char	*cmd;
	void	(*func)(t_minishell *minishell, char **arr);
	int		argc;
	char	*opt;
};

#endif