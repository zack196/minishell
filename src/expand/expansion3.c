/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:57:29 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 00:21:29 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	exp_here(int curr, int next)
{
	if (curr == '$' && next == '?')
		return (1);
	if (curr == '$' && !must_expand(next))
		return (1);
	return (0);
}

int	count(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while (str[i] && !must_expand(str[i]))
		i++;
	return (i);
}

void	ft_free_2(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	free(str2);
	free(str3);
}

void	expand_var(t_envi *env, char **content)
{
	t_help	h;

	h.str = NULL;
	h.str1 = NULL;
	h.join = NULL;
	h.last_str = NULL;
	h.i = 0;
	h.prev = *content;
	h.dollar_count = count_consecutive_dollars(*content);
	if ((h.dollar_count % 2) == 0)
		return ;
	while (h.prev[h.i] && !exp_here(h.prev[h.i], h.prev[h.i + 1]))
		h.i++;
	if (!h.prev[h.i] || !h.prev[h.i + 1])
		return ;
	if (h.i)
		h.str = ft_substr(h.prev, 0, h.i);
	h.j = h.i + 1 + count(h.prev + h.i + 1);
	h.str1 = get_value_of_exp(env, ft_substr(h.prev, h.i + 1, h.j - h.i - 1));
	h.join = ft_strjoin(h.str, h.str1);
	if (ft_strlen(h.prev + h.j))
		h.last_str = ft_substr(h.prev, h.j, ft_strlen(h.prev + h.j));
	*content = ft_strjoin(h.join, h.last_str);
	ft_free_2(h.last_str, h.prev, h.str1);
	expand_var(env, content);
}
