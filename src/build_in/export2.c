/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:23:18 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/05 22:36:59 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	export_node(t_envi **envi, char *key, char *value, int append)
{
	t_envi	*ptr;

	ptr = *envi;
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, key))
			break ;
		ptr = ptr->next;
	}
	if (!ptr)
		return (ft_lstadd_back_env(envi, ft_lstnew_env(key, value, 0)));
	if (append == 1)
	{
		ptr->value = ft_strjoin(ptr->value, value);
		free(value);
	}
	else if (value)
	{
		free(ptr->value);
		ptr->value = value;
	}
	free(key);
}

t_envi	*cpy_env(t_envi *envi)
{
	t_envi	*cpy;

	cpy = NULL;
	while (envi)
	{
		if (envi->value)
			ft_lstadd_back_env(&cpy, ft_lstnew_env(ft_strdup(envi->key),
					ft_strdup(envi->value), 0));
		else
			ft_lstadd_back_env(&cpy, ft_lstnew_env(ft_strdup(envi->key),
					NULL, 0));
		envi = envi->next;
	}
	return (cpy);
}

void	print_export(t_envi *cpy)
{
	while (cpy)
	{
		if (ft_strcmp(cpy->key, "?") && cpy->value)
			printf("declare -x %s=\"%s\"\n", cpy->key, cpy->value);
		else if (ft_strcmp(cpy->key, "?"))
			printf("declare -x %s\n", cpy->key);
		cpy = cpy->next;
	}
}
