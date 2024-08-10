#include "../../minishell.h"

t_env	*cpy_env(t_env *env)
{
	t_env	*cpy;
	t_env	*new;

	cpy = NULL;
	while (env)
	{
		new = my_malloc(sizeof (t_env), 0);
		new->var = ft_strdup(env->var);
		new->val = ft_strdup(env->val);
		if (!new->val)
		
			new->line = ft_strjoin(new->var, new->val);
		add_env(&cpy, new);
		env = env->next;
	}
	return (cpy);
}

void	print_env(t_env *env, int mode_export)
{
	while (env)
	{
		if (mode_export == 1 && env->line)
			printf("declare -x %s\n", env->line);
		else if (env->line)
			printf("%s\n", env->line);
		env = env->next;
	}
}

void	_export(t_env *env)
{
	t_env	*cpy;
	t_env	*begin;
	int		bool_swap;
	char	*line;

	cpy = cpy_env(env);
	while (1)
	{
		bool_swap = 0;
		begin = cpy;
		while (begin->next)
		{
			if (ft_strcmp(begin->line, begin->next->line) < 0)
			{
				line = begin->line;
				begin->line = begin->next->line;
				begin->next->line = line;
				bool_swap = 1;
			}
			begin = begin->next;
		}
		if (bool_swap ==0)
			break;
	}
	print_env(cpy, 1);
}
