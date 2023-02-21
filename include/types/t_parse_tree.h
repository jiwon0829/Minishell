/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parse_tree.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:36 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:38:44 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PARSE_TREE_H
# define T_PARSE_TREE_H

# include "t_token.h"

typedef struct s_parse_tree	t_parse_tree;

struct s_parse_tree
{
	t_parse_tree	*up;
	t_parse_tree	*left;
	t_parse_tree	*right;
	t_token			*token;
	int				type;
};

#endif