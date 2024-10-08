/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:55:41 by namrene           #+#    #+#             */
/*   Updated: 2024/09/05 16:56:30 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
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

int	ft_strchr_2(const char *str, int c)
{
	char			*ptr;
	int				i;
	unsigned char	ch;

	i = 0;
	ptr = (char *)str;
	ch = c;
	if (!str)
		return (0);
	while (ptr[i])
	{
		if (ptr[i] == ch)
			return (i);
		i++;
	}
	if (ptr[i] == ch)
		return (i);
	return (0);
}

void	clear_cmds(t_cmd **cmd)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	if (!cmd || !*cmd)
		return ;
	tmp1 = *cmd;
	while (tmp1)
	{
		if (tmp1->red)
			ft_lstclear_2(&tmp1->red);
		if (tmp1->red)
			ft_lstclear_2(&tmp1->red);
		if (tmp1->cmd)
			ft_free_tab2(tmp1->cmd);
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
}
