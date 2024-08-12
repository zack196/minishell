#include "../../minishell.h"

void	cd(const char *path, t_env **sh_env)
{
	t_env	*env;
	t_env	*oldpwd;
	char	*old_path;

	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		exit(1);
	}
	env = *sh_env;
	oldpwd = NULL;
	while (env)
	{
		
		if (!ft_strcmp("PWD", env->var))
		{
			old_path = ft_strdup(env->val);
			env->val = ft_strjoin(env->val, ft_strjoin("/", path));
			env->line = ft_strjoin(env->var, ft_strjoin("=", env->val));
		}
		if (!ft_strcmp(env->var, "OLDPWD"))
			oldpwd = env;
		env = env->next;
	}
	if (!oldpwd)
		export(sh_env, ft_strjoin("OLDPWD=", old_path));
	else
	{
		oldpwd->val = old_path;
		oldpwd->line = ft_strjoin(oldpwd->var, ft_strjoin("=", oldpwd->val));
	}
}
