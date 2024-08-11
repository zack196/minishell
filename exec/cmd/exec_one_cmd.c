#include "../../minishell.h"

char	**get_path_env(t_env *sh_env)
{
	char	**env;
	int		i;

	env = NULL;
	i = 0;
	while (sh_env)
	{
		if (!ft_strcmp(sh_env->var, "PATH"))
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

void	exec_cmd(t_env *sh_env, char **cmd)
{
	char	*path;
	char	**env;
	char	**cmd_arg;

	path = get_cmd_path(sh_env, *cmd);
	env = get_path_env(sh_env);
	execve(path, cmd, env);
}

void	exec_build_in(t_env **sh_env, char **cmd, int *bool_build_in)
{
	if (!ft_strcmp(*cmd, "cd"))
		cd(*(cmd + 1));
	else if (!ft_strcmp(*cmd, "echo"))
	{
		if (!ft_strncmp(*(cmd + 1), "-n", 2))
			echo((cmd + 2), 1);
		else
			echo((cmd + 1), 0);
	}
	else if (!ft_strcmp(*cmd, "env"))
		print_env(*sh_env, 0);
	else if (!ft_strcmp(*cmd, "exit"))
		env_exit(*(cmd + 1));
	else if (!ft_strcmp(*cmd, "pwd"))
		pwd();
	else if (!ft_strcmp(*cmd, "unset"))
		unset(sh_env, *(cmd + 1));
	else if (!ft_strcmp(*cmd, "export"))
	{
		if (!*(++cmd))
		{
			// printf("in\n");
			_export(*sh_env);
		}
		else
			while (*cmd)
				export(sh_env, *(cmd++));
	}
	else
		*bool_build_in = 0;
}

void	proc(int fd_in, int fd_out, t_env **sh_env, char **cmd)
{
	int	bool_build_in;

	bool_build_in = 1;
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		ft_putstr_fd(*cmd, 2);
		perror(" error dup2");
		my_malloc(2, 1); // free heap
		exit(1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error dup");
		my_malloc(2, 1); // free heap
		exit(1);
	}
	exec_build_in(sh_env, cmd, &bool_build_in);
	if (!bool_build_in)
		exec_cmd(*sh_env, cmd);
}
