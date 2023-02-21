/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:48:22 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:49:09 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

# include <stdio.h>
# include "minishell.h"
# include "../libft/libft.h"

void	export_error_message(char *msg);
void	unset_error_message(char *msg);
int		snytax_error_message(char *msg);
void	exit_err_massage(t_minishell *minishell, int status, char *msg);
void	err_massage(t_minishell *minishell, int status, char *msg);
int		snytax_error_message(char *msg);
void	exit_argment_error(char *msg);
void	exit_argment_cnt_error(void);
void	memory_malloc_error(void);

#endif
