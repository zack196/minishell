#include "../../includes/parse.h"

t_envi	*ft_lstnew_env(char *key, char *value, int is_min)
{
	t_envi	*new;

	new = (t_envi *)malloc(sizeof(t_envi));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->is_min = is_min;
	new->next = NULL;
	return (new);
}

t_envi	*ft_lstlast_env(t_envi *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_envi **lst, t_envi *new)
{
	t_envi	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = new;
}

void	ft_remove(t_token *tmp, t_token **curr, t_token **token)
{
	t_token	*exp;

	if (!tmp)
	{
		*token = (*curr)->next;
		ft_lstdelone_t(*curr);
		(*curr) = NULL;
	}
	else
	{
		exp = (*curr)->next;
		ft_lstdelone_t(*curr);
		tmp->next = exp;
		*curr = exp;
	}
}

int	ft_putendl_fd_2(char *s, char *str, int fd)
{
	if (!s)
	{
		write (fd, "\n", 1);
		return (0);
	}
	if (str && *str == '/')
		str++;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
	if (str)
	{
		write(fd, "`", 1);
		while (*str)
		{
			write (fd, str, 1);
			str++;
		}
		write(fd, "\'", 1);
	}
	write (fd, "\n", 1);
	return (0);
}
