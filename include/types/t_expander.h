/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_expander.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:37:58 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:44:50 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXPANDER_H
# define T_EXPANDER_H

typedef struct s_expander	t_expander;

struct s_expander
{
	int		ret;
	int		j;
	int		k;
	int		exit_flag;
	char	*first_str;
	char	*middle_str;
	char	*change_str;
	char	*last_str;
	char	*return_str;
};

#endif
