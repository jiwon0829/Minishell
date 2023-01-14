#include "envp.h"
#include "../../libft/libft.h"

void    insert_envp(t_envp **node, const char *key, const char *value)
{
    t_envp  *new;
    t_envp  *head;

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

void    delete_envp(t_envp **node, const char *key)
{
    t_envp  *head;
    t_envp  *tmp;

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