#include "minishell.h"

char	*get_var(char *line, t_shell *shell)
{
	char	*var;
	int		i;
	
	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	var = my_malloc(i + 1, shell);
	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
	{
		var[i] = line[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

char	*get_val(char *line, int *bool, t_shell *shell)
{
	char	*val;
	int		i;

	i = 0;
	while (line[i] && line[i] != '+' && line[i] != '=')
		i++;
	if (!line[i])
		return (NULL);
	if (line[i] && line[i] == '+')
	{
		*bool = 1;
		val = ft_strdup(line + i + 2, shell); 
	}
	else
		val = ft_strdup(line + i + 1, shell);
	return (val);
}

char	*get_line(char *var, char *val, t_shell *shell)
{
	char *line;

	if (!*val)
		return (var);
	line = ft_strjoin(var, "=", shell);
	line = ft_strjoin(line, val, shell);
	return (line);
}

int	check_line(char *line)
{
	if (!(('a' <= *line && *line <='z')
		|| ('A' <= *line && *line <='Z') || *line == '_'))
		{
			return (0);
		}
	while (*line && *line != '=' && *line != '+')
	{
		if (!(('A' <= *line && *line <='Z') || ('a' <= *line && *line <='z')
			|| *line == '_' || ('0' <= *line && *line <='9')))
			return (0);
		line++;
	}
	if (*line == '+' && *(line + 1) != '=')
		return (0);
	return (1);

}

t_env	*new_env(char *line, t_shell *shell)
{
	t_env	*new;
	int		i;

	if (!check_line(line))
	{
		return (my_free(shell), error_msg(line), NULL);
	}
	new = my_malloc(sizeof (t_env), shell);
	new->var = get_var(line, shell);
	i = 0;
	new->val = get_val(line, &i, shell);
	if (new->val)
		new->line = get_line(new->var, new->val, shell);
	return (new);
}

void	add_to_back(t_env **env, t_env *new)
{
	t_env	*loc;

	if (!*env)
	{
		*env = new;
		return ;
	}
	loc = *env;
	while (loc->next)
		loc = loc->next;
	loc->next = new;
}

void	init_env(t_shell *shell, char **env)
{
	int	i;
	t_env *new;

	i = -1;
	while (env[++i])
	{
		new = new_env(env[i], shell);
		add_to_back(&shell->env, new);
	}
}

void	export(char *line, t_shell *shell)
{
	t_env	*env;
	char	*val;
	int		bool_append_mode;
	char	*var;

	bool_append_mode = 0;
	env = shell->env;
	val = get_val(line, &bool_append_mode, shell);
	var = get_var(line, shell);
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			break;
		env = env->next;
	}
	if (!env)
		add_to_back(&shell->env, new_env(line, shell));
	else if (env && bool_append_mode == 1)
	{
		env->val = ft_strjoin(env->val, val, shell);
		env->line = get_line(env->var, env->val, shell);
	}
	else if (env && bool_append_mode == 0)
	{
		env->val = val;
		env->line = get_line(env->var, env->val, shell);
	}
}

void	unset(t_shell *shell, char *var)
{
	t_env	*env;
	t_env	*line_befor;
	t_env	*line_after;

	env = shell->env;
	line_after = NULL;
	line_befor = NULL;
	if (!ft_strcmp(var, env->var))
	{
		shell->env = env->next;
		return ;
	}
	while (env)
	{
		if (!ft_strcmp(var, (env->next)->var))
		{
			line_befor = env;
			line_after = env->next->next;
			break ; 
		}
		env = env->next;
	}
	line_befor->next = line_after;
}

void	environment(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->line)
			printf("%s\n", env->line);
		env = env->next;
	}
}

void	pwd()
{
	char	*dir;

	dir = malloc(4096 * sizeof (char));
	getcwd(dir, 4096);
	printf("%s\n", dir);
	free(dir);
}

void	echo(char **argv, int ac)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		ft_putstr(argv[i]);
		if (i < ac - 1)
			write(1, " ", 1);
	}
}