#include "../../minishell.h"

int		check_export(char *line, int *append)
{
	if (*line && !ft_isalpha(*line))
		return (0);
	line++;
	while (*line && ft_isalnum(*line) && *line != '_' && *line != '+' && *line != '=')
		line++;
	if (*line == '+' && *(line + 1) != '=')
		return (0);
	else if (*line == '+' && *(line + 1) == '=')
		*append = 1;
	return (1);
}

void	export(t_env **envi, char *line)
{
	t_env	*env;
	int		append_mode;

	env = *envi;
	append_mode = 0;
	if (!check_export(line, &append_mode))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
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
	else if (env && !append_mode && !get_val_env(line))
		return ;
	else if (env && !append_mode && get_val_env(line))
	{
		env->val = get_val_env(line);
		env->line = ft_strjoin(env->var, ft_strjoin("=", env->val));
	}
	else
		add_env(envi, new_element_env(line));
}

t_env	*line_clone(char *var, char *val)
{
	t_env	*new;

	new = my_malloc(sizeof (t_env), 0);
	new->next = NULL;
	new->var = ft_strdup(var);
	new->val = NULL;
	if (val)
	{
		new->val = ft_strdup(val);
		new->line = ft_strjoin(new->var, ft_strjoin("=", ft_strjoin("\"", ft_strjoin(new->val, "\""))));
		return (new);
	}
	new->line = new->var;
	return (new);
}

t_env	*cpy_env(t_env *env)
{
	t_env	*cpy;
	t_env	*new;

	cpy = NULL;
	while (env)
	{
		new = line_clone(env->var, env->val);
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
			if (ft_strcmp(begin->line, begin->next->line) <= 0)
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
