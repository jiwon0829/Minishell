/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:08:51 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 17:08:52 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "error_message.h"

void	memory_malloc_error(void)
{
	ft_putendl_fd("memory malloc fail", 2);
	exit (1);
}
