#include "../../minishell.h"

void    unset(t_env **envi, char *var)
{
	t_env   *env;
	t_env   *unset_node;

	// test if var is a valid variable //TODO
	
	if (!ft_strcmp(var, (*envi)->var))
	{
		unset_node = *envi;
		*envi = (*envi)->next;
		unset_node->next = NULL;
		return ;
	}
	env = *envi;
	unset_node = NULL;
	while (env)
	{
		if (!ft_strcmp(var, env->next->var))
		{
			unset_node = env->next;
		    break ;
		}
		env = env->next;
	}
	if (unset_node && env->next)
	{
		env->next = env->next->next;
		unset_node->next = NULL;
	}
	else if (unset_node && !env->next)
	{
		unset_node->next = NULL;
		env->next = NULL;
	}
}
