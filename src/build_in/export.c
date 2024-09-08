/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:23:56 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/07 17:35:49 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	get_idx(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	_export(char *line, t_envi **envi)
{
	char	*key;
	char	*value;
	int		append;
	int		equal;
	int		plus;

	equal = get_idx(line, '=');
	plus = get_idx(line, '+');
	append = 0;
	if (plus + 1 == equal)
	{
		append = 1;
		key = ft_substr(line, 0, plus);
	}
	else
		key = ft_substr(line, 0, equal);
	if (!check_var(key, "export", envi))
		return (free(key), 1);
	if (equal != -1)
		value = ft_substr(line + equal + 1, 0, ft_strlen(line) - equal);
	else
		value = NULL;
	export_node(envi, key, value, append);
	return (0);
}

void	swap_node_values(t_envi *a, t_envi *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_export(t_envi *envi)
{
	t_envi	*cpy;
	t_envi	*ptr;
	int		sort_over;

	cpy = cpy_env(envi);
	while (1)
	{
		sort_over = 1;
		ptr = cpy;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_node_values(ptr, ptr->next);
				sort_over = 0;
			}
			ptr = ptr->next;
		}
		if (sort_over)
			break ;
	}
	print_export(cpy);
	ft_free_env(&cpy);
}

int	export(char **av, t_envi **envi)
{
	int	exit_stat;
	int	i;

	i = 0;
	exit_stat = 0;
	if (!av[i])
		sort_export(*envi);
	else
	{
		while (av[i])
		{
			if (_export(av[i++], envi))
				exit_stat = 1;
		}
	}
	return (exit_stat);
}
