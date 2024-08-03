#include "../minishell.h"

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

char	*get_var(char *line)
{
	int		i;
	char	*var;

	i = 0;

	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	if (line[i] == '=' || line[i] == '+')
		i++;
	var = my_malloc(i + 1, 0);
	var[i] = '\0';
	if ((line[i] == '=' || line[i] == '+') && i)
		var[--i] = '=';
	while (--i >= 0)
		var[i] = line[i];
	if (!check_var_name(var))
		return (printf("bash: \'%s\': not a valid identifier\n", line), my_malloc(0, 1), NULL);
	return (var);
}

char	*get_val(char *line, int *append)
{
	int		i;
	// int		j;
	char	*val;

	i = 0;
	*append = 0;
	while (line[i] && line[i] != '+' && line[i] != '=')
		i++;
	if (!line[i])
		return (ft_strdup(""));
	else if (line[i] == '+' && line[i + 1] == '=')
	{
		i = i + 2;
		*append = 1;
	}
	else if (line[i] == '=')//var=val
		i++;
	val = ft_strdup(line + i);
	return (val);
}

t_env	*new_element_env(char *line)
{
	char	*var;
	char	*val;
	t_env	*new;
	int		append;

	var = get_var(line);
	if (!*var)
		return (printf("error message\n"), my_malloc(2, 1), exit(1), NULL);
	val = get_val(line, &append);
	new = my_malloc(sizeof (t_env), 0);
	new->next = NULL;
	new->var = var;
	new->val = val;
	if (!ft_strrchr(var, '='))
		return (new);
	new->line = ft_strjoin(new->var, new->val);
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	
}

void	init_env(t_env **shell_env, char **env)
{
	int	i;
	t_env	*new;

	i = -1;
	while (env[++i])
	{
		new = new_element_env(env[i]);
		add_env(shell_env, new);
	}
}