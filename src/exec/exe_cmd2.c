/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:51:48 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/07 18:03:55 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	error_cmd(char *cmd, char *err_msg, int n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(err_msg, 2);
	exit(n);
}

char	**remove_empty_string(char **ptr)
{
	char	**res;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (ptr[++i])
		if (sp_cmp(ptr[i]) == 0)
			size++;
	if (size == 0)
		return (NULL);
	res = malloc((size + 1) * sizeof (char *));
	if (!res)
		return (NULL);
	size = 0;
	i = -1;
	while (ptr[++i])
		if (sp_cmp(ptr[i]) == 0)
			res[size++] = ptr[i];
	res[size] = NULL;
	return (res);
}

int	alloc_size(char **cmd)
{
	char	**tmp;
	int		i;
	int		size;
	int		j;

	i = -1;
	size = 0;
	while (cmd[++i])
	{
		tmp = ft_split(cmd[i], 127);
		if (tmp && !tmp[0])
		{
			size++;
			ft_free_tab2(tmp);
			continue ;
		}
		j = -1;
		while (tmp && tmp[++j])
			size++;
		ft_free_tab2(tmp);
	}
	return (size);
}

void	fill_res(char **cmd, char **res)
{
	int		size;
	int		i;
	char	**tmp;
	int		j;

	size = 0;
	i = -1;
	while (cmd[++i])
	{
		tmp = ft_split(cmd[i], 127);
		if (tmp && !tmp[0])
		{
			res[size++] = ft_strdup("");
			ft_free_tab2(tmp);
			continue ;
		}
		j = -1;
		while (tmp && tmp[++j])
			res[size++] = ft_strdup(tmp[j]);
		ft_free_tab2(tmp);
	}
	res[size] = NULL;
}

char	**exec_expand(char **cmd)
{
	char	**res;

	res = malloc(sizeof (char *) * (alloc_size(cmd) + 1));
	if (!res)
		return (NULL);
	fill_res(cmd, res);
	return (ft_free_tab2(cmd), res);
}
