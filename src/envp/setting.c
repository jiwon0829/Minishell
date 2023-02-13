/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:44:38 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 14:48:12 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "../libft/libft.h"

void	get_key(t_envp *node, const char *envp)
{
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		++len;
	node->key = ft_substr(envp, 0, len);
}

void	get_value(t_envp *node, const char *envp)
{
	int	len;

	len = ft_strlen(envp) - ft_strlen(node->key) - 1;
	node->value = ft_substr(envp, ft_strlen(node->key) + 1, len);
}

void	init_envp(t_envp **node, char **envp)
{
	int		i;
	t_envp	**head;

	head = node;
	i = 0;
	while (envp[i])
	{
		*node = malloc(sizeof(t_envp));
		(*node)->next = NULL;
		get_key(*node, envp[i]);
		get_value(*node, envp[i]);
		node = &((*node)->next);
		++i;
	}
	*node = NULL;
	(*head)->cnt = i;
}

char	**envp_to_dptr(t_envp *head)
{
	char	**ret;
	char	*str;
	int		i;

	ret = malloc(sizeof(char *) * (head->cnt + 1));
	i = 0;
	while (head)
	{
		ret[i] = ft_strjoin(head->key, "=");
		str = ft_strjoin(ret[i], head->value);
		free(ret[i]);ret[i] = NULL;
		ret[i] = ft_strdup(str);
		head = head->next;
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

t_envp	*get_envpnode(t_envp *head, const char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	return (head);
}
