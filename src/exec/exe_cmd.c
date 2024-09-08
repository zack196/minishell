/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:24:22 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 12:56:23 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static void	sp_free(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i])
		free(env[i]);
}

char	**get_env(t_envi *envi)
{
	char	**env;

	while (envi)
	{
		if (ft_strcmp(envi->key, "PATH") == 0)
			break ;
		envi = envi->next;
	}
	env = NULL;
	if (envi)
		env = ft_split(envi->value, ':');
	return (env);
}

char	*get_path_cmd(char *cmd, char **env)
{
	char	*path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (sp_free(env), free(env), ft_strdup(cmd));
	if (!env || ft_strchr(cmd, '/'))
		error_cmd(cmd, ": No such file or directory\n", 127);
	i = -1;
	while (env && env[++i])
	{
		path = ft_strjoin(ft_strjoin(env[i], "/"), cmd);
		if (!access(path, F_OK))
			return (sp_free(env + i + 1), free(env), path);
		free(path);
	}
	free(env);
	return (NULL);
}

int	count_env(t_envi *envi)
{
	int	i;

	i = 0;
	while (envi)
	{
		if (envi->value)
			i++;
		envi = envi->next;
	}
	return (i);
}

void	sh_level(t_envi *envi)
{
	int	pl_holder;

	pl_holder = ft_atoi(envi->value);
	free(envi->value);
	if (pl_holder < 0)
		envi->value = ft_strdup("0");
	else if (pl_holder >= 999)
		envi->value = ft_strdup("");
	else
		envi->value = ft_itoa(pl_holder + 1);
}
