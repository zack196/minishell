/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:52:30 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/09/08 12:31:10 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	**execve_env(t_envi *envi)
{
	char	**env;
	int		i;

	i = count_env(envi);
	env = malloc((i + 1) * sizeof (char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envi)
	{
		if (envi->key && !ft_strcmp(envi->key, "SHLVL") && envi->value)
			sh_level(envi);
		if (envi->value)
			env[i++] = ft_strjoin(ft_strjoin(ft_strdup(envi->key),
						"="), envi->value);
		envi = envi->next;
	}
	env[i] = NULL;
	return (env);
}

void	no_eacces(char *path, char **cmd)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_cmd(path, ": No such file or directory\n", 1);
	else
	{
		close(fd);
		error_cmd(*cmd, ": command not found\n", 127);
	}
}

void	after_exec(char *path, char **cmd)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			error_cmd(path, ": is a directory\n", 126);
		else
		{
			if (access(path, X_OK) == -1)
			{
				if (errno == EACCES)
					error_cmd(path, ": Permission denied\n", 126);
			}
			else
				no_eacces(path, cmd);
		}
	}
	else
		error_cmd(path, ": No such file or directory\n", 127);
}

int	size_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	exe_cmd(char **cmd, t_envi *envi, int fd_in, int fd_out)
{
	char	**env;
	int		exit_code;
	char	*path;
	char	**cmd_prim;

	cmd = exec_expand(cmd);
	cmd_prim = remove_empty_string(cmd);
	if (!cmd || !*cmd || !cmd_prim || !*cmd_prim)
		return (exit(0));
	if (cmd_prim && *cmd_prim && is_build(cmd_prim))
	{
		exit_code = build_in(cmd, &envi);
		return (close(fd_in), close(fd_out), free(cmd_prim), exit(exit_code));
	}
	env = get_env(envi);
	path = get_path_cmd(*cmd_prim, env);
	if (!path)
		error_cmd(*cmd_prim, ": command not found\n", 127);
	env = execve_env(envi);
	execve(path, cmd_prim, env);
	after_exec(path, cmd_prim);
	free(path);
	free(cmd_prim);
}
