#include "../../minishell.h"


void	export(t_env **envi, char *line)
{
	t_env	*env;
	int		append_mode;

	env = *envi;
	append_mode = 0;
	if (ft_strrchr(line, '+'))
		append_mode = 1;
	while (env)
	{
		if (!ft_strcmp(env->var, get_var_env(line)))
			break ;
		env = env->next;
	}
	if (env && append_mode)
	{
		env->val = ft_strjoin(env->val, get_val_env(line));
		env->line = ft_strjoin(env->var, ft_strjoin("=", env->val));
	}
	else
		add_env(envi, new_element_env(line));
}

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
		printf("%s\n", new->line);
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
	printf("%s\n",cpy->line);
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
