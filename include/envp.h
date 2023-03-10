/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:57 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:48:16 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include <stdlib.h>
# include "types/t_minishell.h"
# include "types/t_envp.h"

void	get_key(t_envp *node, const char *envp);
void	get_value(t_envp *node, const char *envp);
void	insert_envp(t_envp **node, const char *key, const char *value);
void	remove_envp(t_envp **node, const char *key);
t_envp	*get_envpnode(t_envp *head, const char *key);
char	**envp_to_dptr(t_envp *head);
t_envp	*find_envp(t_envp *head, char *key);
char	*find_envp_value(t_envp *head, char *key);
void	update_envp(t_envp *head, char *key, char *new);
void	delete_envp(t_envp *head);
void	print_envp(t_minishell *minishell);
void	print_sort_envp(t_minishell *minishell);

#endif
