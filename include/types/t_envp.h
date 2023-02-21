/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:37:40 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:37:45 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENVP_H
# define T_ENVP_H

typedef struct s_envp	t_envp;

struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
	int		cnt;
};

#endif
