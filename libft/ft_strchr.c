/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:08:32 by namrene           #+#    #+#             */
/*   Updated: 2024/09/05 21:08:32 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	symbole;

	str = (char *)s;
	symbole = (char)c;
	while (*str && !(*str == symbole))
		str++;
	if (*str == symbole)
		return (str);
	return (0);
}
