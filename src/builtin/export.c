/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:34:46 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/21 19:43:30 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_variable_name(const char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (FALSE);
	while (*name && *name != '=')
	{
		if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

void	split_key_value(t_envp *envp, char *str)
{
	char	*key;
	char	*value;
	char	*sign;

	sign = ft_strchr(str, '=');
	key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(sign));
	if (sign)
	{
		value = ft_substr(sign, 1, ft_strlen(sign) - 1);
		if (!value)
			value = ft_strdup("");
		if (find_envp(envp, key))
			update_envp(envp, key, value);
		else
			insert_envp(&envp, key, value);
		free(value);
	}
	else if (!sign && !find_envp(envp, key))
	{
		free(key);
		key = ft_strdup(str);
		insert_envp(&envp, key, 0);
	}
	free(key);
}

void	export(t_minishell *minishell, char **arr)
{
	int	i;

	i = 1;
	if (!arr[1])
	{
		print_sort_envp(minishell);
		return ;
	}
	while (arr[i])
	{
		if (!check_variable_name(arr[i]))
		{
			minishell->exit_status = 1;
			export_error_message(arr[i]);
		}
		else
		{
			split_key_value(minishell->envp, arr[i]);
		}
		++i;
	}
}
