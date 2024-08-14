#include "../minishell.h"

char	*get_var_env(char *line)
{
	int		i;
	char	*var;

	i = 0;

	while (line[i] != '\0' && line[i] != '=' && line[i] != '+')//var=val
		i++;
	var = my_malloc((i + 1) * sizeof (char), 0);
	var[i--] = '\0';
	while (i >= 0)
	{
		var[i] = line[i];
		i--;
	}
	return (var);
}

char	*get_val_env(char *line)
{
	char	*val;

	while (*line && *line != '=')
		line++;
	if (!*line)
		return (NULL);
	else if (*line == '=')
		line++;
	val = ft_strdup(line);
	return (val);
}

int	check_var_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

t_env   *new_element_env(char *line)
{
    t_env   *new;

    new = my_malloc(sizeof (t_env), 0);
	new->var = get_var_env(line);
	if (!check_var_name(new->var))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		my_malloc(1, 1);
	}
    new->val = get_val_env(line);
    if (!new->val)
		new->line = NULL;
	else
		new->line = ft_strjoin(ft_strjoin(new->var, "="), new->val);
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*ptr;

	ptr = *env;
	if (!*env)
	{
		*env = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	init_env(t_env **sh_env, char **env)
{
	int	i;

	i = 0;
	add_env(sh_env, new_element_env("OLDPWD"));
	if (!env[0])
	{
		(*sh_env)->is_min = 1;
		add_env(sh_env, new_element_env("PWD=/Users/zel-oirg/Desktop/minishell"));
		add_env(sh_env, new_element_env("SHLVL=1"));
		return ;
	}
	print_env(*sh_env, 0);
	while (env[i])
	{
		(*sh_env)->is_min = 0;
		add_env(sh_env, new_element_env(env[i]));
		i++;
	}
}
