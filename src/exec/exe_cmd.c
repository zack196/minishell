#include "../../includes/parse.h"

 void	error_cmd(char *cmd, char *err_msg, int n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(err_msg, 2);
	exit(n);
}

static void	sp_free(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i])
		free(env[i]);
}

char    **get_env(t_envi *envi)
{
    char    **env;

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

char    *get_path_cmd(char *cmd, char **env)
{
    char	*path;
    int		i;

	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
        return (sp_free(env), free(env), ft_strdup(cmd));
	if (!env || ft_strchr(cmd, '/'))
	{
		error_cmd(cmd, ": No such file or directory\n", 127);
	}
	i = -1;
    while (env && env[++i])
	{
		path = ft_strjoin(ft_strjoin(env[i], "/"), cmd);
		if (!access(path, F_OK))
		{
			sp_free(env + i + 1);
			free(env);
			return (path);
		}
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

char	**execve_env(t_envi *envi)
{
	char	**env;
	int		i;
	int		pl_holder;

	i = count_env(envi);
	env = malloc((i + 1) * sizeof (char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envi)
	{
		if (envi->key && !ft_strcmp(envi->key, "SHLVL") && envi->value)
		{
			pl_holder = ft_atoi(envi->value);
			free(envi->value);
			if (pl_holder < 0)
				envi->value = ft_strdup("0");
			else if (pl_holder >= 999)
				envi->value = ft_strdup("");
			else
				envi->value = ft_itoa(pl_holder + 1);
		}
		if (envi->value)
			env[i++] = ft_strjoin(ft_strjoin(ft_strdup(envi->key), "="), envi->value);
		envi = envi->next;
	}
	env[i] = NULL;
	return (env);
}

void	fct1(char *path, char **cmd)
{
    struct stat statbuf;

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
			{
	            int fd = open(path, O_RDONLY);
	            if (fd == -1)
	                error_cmd(path, ": No such file or directory\n", 1);
	            else
				{
	                close(fd);
	                error_cmd(*cmd, ": command not found\n", 127);
	            }
	        }
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

char	**remove_empty_string(char **ptr)
{
	char	**res;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (ptr[++i])
		if (*ptr[i])
			size++;
	res = malloc((size + 1) * sizeof (char *));
	if (!res)
		return (NULL);
	size = 0;
	i = -1;
	while (ptr[++i])
	{
		if (*ptr[i])
			res[size++] = ft_strdup(ptr[i]);
		free(ptr[i]);	
	}
	res[size] = NULL;
	free(ptr);
	return (res);
}

char	**alloc_size(char **cmd)
{
	char	**res;
	char	**tmp;
	int		i;
	int		size;
	int		j;

	i = -1;
	size = 0;
	while (cmd[++i])
	{
		tmp = ft_split(cmd[i], 127);
		if (tmp && !tmp[0])
		{
			size++;
			continue ;
		}
		j = -1;
		while (tmp && tmp[++j])
			size++;
		ft_free_tab2(tmp);
	}
	res = malloc(sizeof (char *) * (size + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	**exec_expand(char **cmd)
{
	char	**res;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	res = alloc_size(cmd);
	if (!res)
		return (NULL);
	size = 0;
	i = -1;
	while (cmd[++i])
	{
		tmp = ft_split(cmd[i], 127);
		if (tmp && !tmp[0])
			res[size++] = ft_strdup("");
		j = -1;
		while (tmp && tmp[++j])
			res[size++] = ft_strdup(tmp[j]);
		ft_free_tab2(tmp);
	}
	res[size] = NULL;
	return (res);
}

void	exe_cmd(char **cmd, t_envi *envi)
{
    char    **env;
	int		exit_code;
    char    *path;

	if (!cmd || !*cmd)
		return ;
	if (is_build(*cmd))
	{
        exit_code =	build_in(cmd, &envi);
        exit(exit_code);
    }
	cmd = exec_expand(cmd);
	cmd = remove_empty_string(cmd);
	env = get_env(envi);
    path = get_path_cmd(*cmd, env);
    if (!path)
        error_cmd(*cmd, ": command not found\n", 127);
    env = execve_env(envi);
    execve(path, cmd, env);
	fct1(path, cmd);
    free(path);
}
