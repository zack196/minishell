/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:23:46 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 12:55:26 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	env(t_envi *envi)
{
	while (envi)
	{
		if (ft_strcmp(envi->key, "?") && envi->value)
			printf("%s=%s\n", envi->key, envi->value);
		envi = envi->next;
	}
	return (0);
}

void	clean_heredoc(char **heredoc)
{
	int	i;

	i = -1;
	while (heredoc && heredoc[++i])
	{
		unlink(heredoc[i]);
		free(heredoc[i]);
	}
}

char	*remove_quot(char *str)
{
	char	*res;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
		if (str[i] != '\"')
			size++;
	res = malloc((size + 1) * sizeof (char));
	i = -1;
	size = 0;
	while (str[++i])
		if (str[i] != '\"')
			res[size++] = str[i];
	res[size] = 0;
	return (res);
}
