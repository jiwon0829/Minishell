/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:41:34 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/02/13 09:48:01 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "../../libft/libft.h"

void	insert_envp(t_envp **node, const char *key, const char *value)
{
	t_envp	*new;
	t_envp	*head;

	head = *node;
	while (*node && ft_strncmp((*node)->key, key, ft_strlen(key) + 1))
		node = &((*node)->next);
	if (*node)
	{
		free((*node)->value);
		if (value)
			(*node)->value = ft_strdup(value);
		else
			(*node)->value = NULL;
	}
	new = malloc(sizeof(t_envp));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	*node = new;
	head->cnt += 1;
}

void	delete_envp(t_envp **node, const char *key)
{
	t_envp	*head;
	t_envp	*tmp;

	head = *node;
	while (*node && ft_strncmp((*node)->key, key, ft_strlen(key) + 1))
		node = &((*node)->next);
	if (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		head->cnt--;
	}
}

t_envp	*find_envp(t_envp *head, char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	return (head);
}

char	*find_envp_value(t_envp *head, char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	if (!head)
		return (NULL);
	return (head->value);
}

void	update_envp(t_envp *head, char *key, char *new)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	free(head->value);
	head->value = NULL;
	head->value = ft_strdup(new);
}
