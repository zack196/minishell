#include "minishell.h"

void	init_sh(t_minishell *sh, char **env)
{
	sh->env = NULL;
	init_env(&sh->env, env);
}

int main(int ac, char **av, char **env)
{
	t_minishell	sh;
	char *line = "var1 var2 var3 var4";

	// sh.env =NULL;
	init_sh(&sh, env);
	export(&sh, line);
	export(&sh, "val");
	// printf("%s\n", sh.env->line);
	export(&sh, "zakaria=el oirghi");
	// export(&sh, "zakaria+= ahmed");
	_env(&sh);
	// _export(&sh);
	my_malloc(0, 1);
}