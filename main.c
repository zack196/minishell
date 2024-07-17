#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
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
	// ac = 1;
	// atexit(ff);
	// av[1] = NULL;
	// char *line;

	init_shell(&shell, env);
	// export("var", &shell);
	// unset(&shell, "USER");
	// environment(&shell);
	// pwd();
	echo(av, ac);
	// while ((line = readline("minishell>")))
	// {
	// 	printf("%s\n", line);
	// }
	
	
	my_free(&shell);
}