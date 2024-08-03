#include"parser.h"
void	ft_lstdelone_t(t_token *lst)
{
	if (lst)
	{
		if (lst->content)
			free(lst->content);
		free(lst);
	}
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*ft_lstnew_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->err = 0;
	new->next = NULL;
	return (new);
}

void	ft_lstclear_t(t_token **lst)
{
	t_token	*tmp;
	t_token	*p;

	if (!lst)
		return ;
	p = *lst;
	while (p)
	{
		tmp = p->next;
		ft_lstdelone_t(p);
		p = tmp;
	}
	*lst = NULL;
}
t_token	*ft_lstlast_m(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_lstadd_back_m(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_m(*lst);
	last->next = new;
}

t_token	*ft_lstnew_m(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->expand = 0;
	new->type = type_token(content);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_redi(t_redi **lst, t_redi *new)
{
	t_redi	*last;

	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

t_redi	*ft_lstnew_redi(char *out, int type)
{
	t_redi	*ptr;

	ptr = malloc(sizeof(t_redi));
	if (!ptr)
		return (NULL);
	ptr->file = out;
	ptr->must_exp = 0;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

t_redi	*ft_lstlast_redi(t_redi *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}