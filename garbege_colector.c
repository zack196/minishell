#include "minishell.h"

t_heap	*ft_lstnew(void *content)
{
	t_heap	*new_node;

	new_node = (t_heap *)malloc(sizeof (t_heap));
	if (!new_node)
		return (NULL);
	new_node -> p_content = content;
	new_node -> next = NULL;
	return (new_node);
}

t_heap	*ft_lstlast(t_heap *lst)
{
	t_heap	*last_node;

	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	last_node = lst;
	return (last_node);
}

void	ft_lstadd_back(t_heap **lst, t_heap *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}

void   	*my_malloc(size_t size, t_shell *shell)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		return (my_free(shell), write(2, "Error malloc!", 13), exit(1), NULL);
	ft_lstadd_back(&shell->heap, ft_lstnew(alloc));
	return (alloc);
}

void    my_free(t_shell *shell)
{
	// ft_lstclear(&shell->heap, free);

	t_heap	*heap;
	t_heap	*tmp;

	heap = shell->heap;
	while (heap)
	{
		tmp = heap;
		heap = heap->next;
		free(tmp->p_content);
		free(tmp);
	}
	
}