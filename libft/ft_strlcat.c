/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:09:20 by namrene           #+#    #+#             */
/*   Updated: 2024/09/05 21:09:20 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(dest);
	i = 0;
	j = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && size - 1 > i + len)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	if (size < len)
		return (ft_strlen(src) + size);
	if (len < size)
		dest[j] = '\0';
	return (len + ft_strlen(src));
}
