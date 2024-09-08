/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namrene <namrene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:33:54 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 00:12:04 by namrene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	trim_quotes(t_token *token)
{
	char	*tmp;

	while (token)
	{
		tmp = token->content;
		if (!*tmp)
		{
			free(tmp);
			token->content = ft_strdup("");
			return ;
		}
		if (token->type == DOUBLE)
		{
			token->content = ft_strtrim(token->content, "\"");
			free(tmp);
		}
		if (token->type == SINGLE)
		{
			token->content = ft_strtrim(token->content, "\'");
			free(tmp);
		}
		token = token->next;
	}
}

char	*sp_dup(void)
{
	char	*s;

	s = malloc(2 * sizeof (char));
	if (!s)
		return (NULL);
	s[0] = 1;
	s[1] = '\0';
	return (s);
}

char	*get_value_of_exp(t_envi *env, char *key)
{
	char	*res;
	int		i;

	while (env && ft_strcmp(env->key, key) != 0)
		env = env->next;
	if (env && ft_strcmp(env->key, key) == 0)
	{
		res = ft_strdup(env->value);
		i = -1;
		while (res[++i])
			if (res[i] == ' ')
				res[i] = 127;
		return (free(key), res);
	}
	return (free(key), sp_dup());
}

void	hyphen_exp(t_token *tok, t_envi *env)
{
	char	*tmp;

	if (tok)
	{
		tmp = tok->content;
		tok->content = get_value_of_exp(env, ft_strdup("HOME"));
		free(tmp);
	}
}

int	must_expand(int next)
{
	if (!ft_isalnum(next) && next != '_')
		return (1);
	return (0);
}
