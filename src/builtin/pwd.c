/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:35:05 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 09:35:13 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	pwd(t_minishell *minishell, char **arr)
{
	char	*path;

	(void)arr;
	path = getcwd(NULL, 0);
	if (!path)
	{
		minishell->exit_status = 1;
		return ;
	}
	printf("%s\n", path);
	free(path);
	path = NULL;
	minishell->exit_status = 0;
}
