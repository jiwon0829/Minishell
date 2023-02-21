/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirect.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:46 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 16:45:27 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_REDIRECT_H
# define T_REDIRECT_H

# include "t_exec.h"
# include "types/t_minishell.h"
# include "lexer.h"

typedef struct s_redirect	t_redirect;

struct s_redirect
{
	int					fd[2];
	int					type;
	char				*file_name;
	struct s_redirect	*next;
};

#endif