/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:11 by zel-oirg          #+#    #+#             */
/*   Updated: 2023/11/30 00:27:15 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)my_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		res[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	res[i] = 0;
	return (res);
}
