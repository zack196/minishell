#include "minishell.h"

void	my_free(t_heap **heap)
{
	t_heap	*tmp;
	t_heap	*tra;

	if (!heap && !*heap)
		return ;
	tra = *heap;
	while (tra)
	{
		tmp = tra->next;
		free(tra->ptr);
		free(tra);
		tra = tmp;
	}
	*heap = NULL;
}

void	*my_malloc(size_t size, int mode_free)
{
	static  t_heap	*heap;
	t_heap			*new;
	void			*ptr;

	if (mode_free == 0)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_putstr_fd("no heap availavle!", 2), my_free(&heap), exit(1), NULL);
		new = malloc(sizeof (t_heap));
		if (!new)
			return (my_free(&heap), exit(1), NULL);
		new->ptr = ptr;
		new->next = NULL;
		if (!heap)
			new->next = heap;
		heap = new;
		return (ptr);
	}
	else
		return (my_free(&heap), NULL);	
}