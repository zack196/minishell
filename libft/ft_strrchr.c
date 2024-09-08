/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:10:00 by namrene           #+#    #+#             */
/*   Updated: 2024/09/05 21:10:00 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cast;

	ptr = (char *)s + ft_strlen(s);
	cast = (char)c;
	while (ptr >= s)
	{
		if (*ptr == cast)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
