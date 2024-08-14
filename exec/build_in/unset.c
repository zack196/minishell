#include "../../minishell.h"

int	bad_identifier(char *var)
{
	if (*var && !ft_isalpha(*var) && *var != '_')
		return (1);
	while (*(++var))
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (1);
	}
	return (0);
}

void    unset(t_env **envi, char *var)
{
	t_env   *env;
	t_env   *unset_node;

	if (bad_identifier(var))
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	if ((*envi)->is_min == 1 && !ft_strcmp(var, "PATH"))
		(*envi)->is_min = 0;
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
		if (env->next && !ft_strcmp(var, env->next->var))
		{
			unset_node = env->next;
		    break ;
		}
		env = env->next;
	}
	if (env && unset_node && env->next)
	{
		env->next = env->next->next;
		unset_node->next = NULL;
	}
	else if (env && unset_node && !env->next)
	{
		unset_node->next = NULL;
		env->next = NULL;
	}
}
