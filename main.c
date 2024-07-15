#include "minishell.h"


t_env	*new_env(char *line, t_shell *shell)
{
	t_env	*new;

	new = my_malloc(sizeof (t_env), shell);
	new->var = ft_strdup_mod(line, shell);
	while (*line != 0 && *line != '=')
		line++;
	if (*line)
		line++;
	new->val = ft_strdup_mod(line, shell);
	new->line = ft_strjoin(new->var, "=", shell);
	new->line = ft_strjoin(new->line, new->val, shell);
	new->next = NULL;
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

	i = -1;
	while (env[++i])
		add_to_back(&shell->env, new_env(env[i], shell));
}

void	init_shell(t_shell *shell, char **env)
{
	// shell->std_in = dup(0);
	// shell->std_out = dup(1);
	// shell->std_err = dup(2);
	shell->heap = malloc(sizeof (t_heap));
	init_env(shell, env);
}

void	ff()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	ac = 1;
	atexit(ff);
	av[1] = NULL;

	init_shell(&shell, env);

	
	my_free(&shell);
}