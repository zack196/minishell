#include "../minishell.h"

void	fct(t_minishell *sh, char *line)
{
	char	**vars;
	int		i;

	i = 0;
	vars = ft_split(line, ' ');
	while (vars[i])
	{
		export(sh, vars[i]);
		i++;
	}
}

void	export(t_minishell *sh, char *line)
{
	t_env	*env;
	char	*var;
	char	*val;
	int		append;

	env = sh->env;
	if (!ft_strrchr(line, '=') && ft_strrchr(line, ' '))
		return (fct(sh, line));
	var = get_var(line);
	while (env)
	{
		if (!ft_strcmp(var, env->var))
			break;
		env = env->next;
	}
	if (!env)
		return (add_env(&sh->env, new_element_env(line)));
	val = get_val(line, &append);
	if (append == 1)
		env->val = ft_strjoin(env->val, val);
	else
		env->val = val;
	env->line = ft_strjoin(env->var, env->val);
}

t_env	*cpy_env(t_minishell *sh)
{
	t_env	*env;
	t_env	*cpy;
	t_env	*new;

	env = sh->env;
	cpy = NULL;
	while (env)
	{
		new = my_malloc(sizeof (t_env), 0);
		new->var = ft_strdup(env->var);
		new->val = ft_strdup(env->val);
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

void	_export(t_minishell *sh)
{
	t_env	*cpy;
	t_env	*begin;
	int		bool_swap;
	char	*line;

	cpy = cpy_env(sh);
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
