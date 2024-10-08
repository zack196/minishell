/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback_m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:55:38 by namrene           #+#    #+#             */
/*   Updated: 2024/09/07 22:55:56 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_token	*ft_lstnew_m(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->expand = 0;
	new->type = type_token(content);
	new->next_starts_with_quote = 0;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_m(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

void	ft_lstdelone_t(t_token *lst)
{
	if (lst)
	{
		if (lst->content)
			free(lst->content);
		free(lst);
	}
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
