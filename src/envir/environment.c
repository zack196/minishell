/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 23:02:20 by namrene           #+#    #+#             */
/*   Updated: 2024/09/08 12:58:02 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	get_idx_of(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	*empty_env(t_envi **envi)
{
	char	*pwd;
	char	buff[PATH_MAX];

	pwd = getcwd(buff, PATH_MAX);
	if (!pwd)
	{
		return (NULL);
	}
	ft_lstadd_back_env(envi,
		ft_lstnew_env(ft_strdup("PWD"), ft_strdup(pwd), 1));
	ft_lstadd_back_env(envi,
		ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lstadd_back_env(envi,
		ft_lstnew_env(ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), 1));
	return (envi);
}

void	*parse_env(char **env, t_envi **dup_env)
{
	int	i;

	i = 0;
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("?"), NULL, 0));
	if (!env)
		return (NULL);
	if (!*env)
		return (empty_env(dup_env));
	while (*env)
	{
		i = get_idx_of(*env, '=');
		ft_lstadd_back_env(dup_env,
			ft_lstnew_env(ft_substr(*env, 0, i),
				ft_substr(*env, i + 1, ft_strlen(*env) - i), 0));
		env++;
	}
	if (!find_node(*dup_env, "OLDPWD"))
		ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("OLDPWD"),
				NULL, 0));
	return (dup_env);
}
