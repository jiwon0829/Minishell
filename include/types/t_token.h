/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:57 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:45:40 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKEN_H
# define T_TOKEN_H

typedef struct s_token	t_token;
typedef struct s_arg	t_arg;

struct s_arg{
	char	**path;
	char	**envp2;
	char	**cmd_arg;
	char	*cmd;
	int		pipe_fd[2];
	int		pid;
};

struct s_token
{
	char	*value;
	int		len;
	int		type;
	int		fd_in;
	int		fd_out;
	t_arg	*arg;
	t_token	*prev;
	t_token	*next;
};

#endif