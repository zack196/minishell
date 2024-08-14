#include "../../minishell.h"

void	cd(const char *path, t_env **sh_env)
{
	t_env	*env;
	char	*old_path;

	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return ;
	}
	env = *sh_env;
	old_path = "";
	while (env)
	{		
		if (!ft_strcmp("PWD", env->var))
		{
			old_path = ft_strdup(env->val);
			env->val = ft_strjoin(env->val, ft_strjoin("/", path));
			env->line = ft_strjoin(env->var, ft_strjoin("=", env->val));
		}	
		env = env->next;
	}
	env = *sh_env;
	while (env)
	{
		if (!ft_strcmp(env->var, "OLDPWD"))
		{
			env->val = old_path;
			env->line = ft_strjoin(ft_strjoin(env->var, "="), env->val);
		}
		env = env->next;
	}
}
