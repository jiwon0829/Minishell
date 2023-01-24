#include "envp.h"
#include "minishell.h"

t_envp *copy_envp(t_envp *head)
{
	t_envp *ret;
	t_envp ret_head;
	int		cnt;

	cnt = 0;
	ret = &ret_head;
	while (head)
	{
		ret->next = malloc(sizeof(t_envp));
		if (!(ret->next))
			return (NULL);
		ret->next->key = ft_strdup(head->key);
		if (head->value)
			ret->next->value = ft_strdup(head->value);
		else
			ret->next->value = NULL;
		head = head->next;
		ret = ret->next;
		++cnt;
	}
	ret->next = NULL;
	ret_head.next->cnt = cnt;
	return (ret_head.next);
}

void	swap_contents_envp(t_envp *node1, t_envp *node2)
{
	char	*key;
	char	*value;

	key = node2->key;
	value = node2->value;
	node2->key = node1->key;
	node2->value = node1->value;
	node1->key = key;
	node1->value = value;
}

t_envp *sort_envp(t_envp *head)
{
	t_envp *ret;
	t_envp *copy;
	t_envp *next;

	copy = copy_envp(head);
	ret = copy;
	while (copy->next)
	{
		next = copy->next;
		while (next)
		{
			if (ft_strncmp(copy->key, next->key, ft_strlen(next->key) + 1) > 0)
				swap_contents_envp(copy, next);
			next = next->next;
		}
		copy = copy->next;
	}
	return (ret);
}

void	print_sort_envp(t_minishell *minishell)
{
	t_envp	*sorted_envp;
	t_envp	*sorted_head;

	sorted_envp = sort_envp(minishell->envp);
	sorted_head = sorted_envp;
	while (sorted_envp)
	{
		printf("%s=%s\n",sorted_envp->key, sorted_envp->value);
		sorted_envp = sorted_envp->next;
	}
	(void)sorted_head;
}

void    print_envp(t_minishell *minishell)
{
	t_envp  *envp;

	envp = minishell->envp;
	while (envp)
	{
		printf("%s=%s\n",envp->key,envp->value);
		envp = envp->next;
	}
}