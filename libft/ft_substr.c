/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:05 by zel-oirg          #+#    #+#             */
/*   Updated: 2023/11/29 23:47:37 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0 || start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen (s) - start)
		len = ft_strlen(s) - start ;
	res = (char *)my_malloc(len + 1, 0);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
