/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:00:59 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/28 12:25:24 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*space_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	*i = sign;
	return ((char *)str);
}

int	ft_atoi(const char *str)
{
	unsigned long	r;
	int				sign;
	int				i;

	r = 0;
	i = 0;
	str = space_sign(str, &sign);
	while (*str == '0')
		str++;
	while ('0' <= *str && *str <= '9' && i < 19)
	{
		r = r * 10 + (*str - '0');
		str++;
		i++;
	}
	if (r <= 9223372036854775807 && (*str < '0' || *str > '9'))
		return ((int)r * sign);
	else
		return (printf("bash: exit: %s: numeric argument required\n", str), exit(255), -1);
}
