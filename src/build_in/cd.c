#include "../../includes/parse.h"
#include <errno.h>
t_envi	*find_node(t_envi *envi, char *key)
{
	t_envi	*ret;

	ret = envi;
	while (ret && ft_strcmp(ret->key, key) != 0)
		ret = ret->next;
	return (ret);
}

void	_set_env(char *key, t_envi **envi, char *new_value)
{
	t_envi	*varr;

	varr = find_node(*envi, key);
	if (varr)
	{
		free(varr->value);
		varr->value = ft_strdup(new_value);
	}
}
void	cd_removed(t_envi **envi, char *path)
{
	t_envi	*pwd;
	t_envi	*oldpwd;

	pwd = find_node(*envi, "PWD");
	oldpwd = find_node(*envi, "OLDPWD");
	if (pwd)
	{
		if (oldpwd)
				oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strjoin(ft_strjoin(pwd->value, "/"), path);
	}
}
int	cd_home(char **path, t_envi *envi)
{
	t_envi	*env_var;

	if (!*path)
	{
		env_var = find_node(envi, "HOME");
		if (env_var)
			*path = ft_strdup(env_var->value);
		else
		{
			set_exit_status(1, &envi);
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		}
	}
	else if (!ft_strcmp(*path, "-"))
	{
		env_var = find_node(envi, "OLDPWD");
		if (!env_var || !env_var->value)
		{
			set_exit_status(1, &envi);
			// g_exit_status = 1;
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		*path = env_var->value;
	}
	return (0);
}
int	cd(char *path, t_envi **envi)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*test_err;

	if (cd_home(&path, *envi))
		return (1);
	getcwd(oldpwd, PATH_MAX);
	if (path && chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		// g_exit_status = 1;
		set_exit_status(1, envi);
		return (1);
	}
	test_err = getcwd(pwd, PATH_MAX);
	if (!test_err)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (cd_removed(envi, path), 0);
	}
	_set_env("OLDPWD", envi, oldpwd);
	_set_env("PWD", envi, pwd);
	set_exit_status(0, envi);
	return (0);
}
