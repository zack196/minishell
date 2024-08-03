#include "../../minishell.h"

char	**get_path_env(t_env *sh_env)
{
	char	**env;
	int		i;

	env = NULL;
	i = 0;
	while (sh_env)
	{
		if (!ft_strcmp(sh_env->var, "PATH="))
		{
			env = ft_split(sh_env->val, ':');
			while (env[i])
			{
				env[i] = ft_strjoin(env[i], "/");
				i++;
			}
			break ;
		}
		sh_env = sh_env->next;
	}
	return (env);
}

char	*get_cmd_path(t_env *sh_env, char *cmd)
{
	char	**env;
	int		i;
	char	*ret;

	if (!access(cmd, F_OK))
		return(cmd);
	env = get_path_env(sh_env);
	i = -1;
	while (env && env[++i])
	{
		ret = ft_strjoin(env[i], cmd);
		if (!access(ret, F_OK))
			return (ret);
	}
	return (NULL);
}

void	exec_cmd(t_env *sh_env, char *cmd)
{
	char	*path;
	char	**env;
	char	**cmd_arg;

	path = get_cmd_path(sh_env, cmd);
	env = get_path_env(sh_env);
	cmd_arg = ft_split(cmd, ' ');
	execve(path, cmd_arg, env);
}