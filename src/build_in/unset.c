#include "../../includes/parse.h"


int check_var(char *var, char *fct, t_envi **envi)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
	{
		set_exit_status(1, envi);
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(fct, 2), ft_putstr_fd(": `", 2)
			, ft_putstr_fd(var, 2), ft_putstr_fd("': not a valid identifier\n", 2), 0);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			set_exit_status(1, envi);
			return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(fct, 2), ft_putstr_fd(": `", 2)
				, ft_putstr_fd(var, 2), ft_putstr_fd("': not a valid identifier\n", 2), 0);
		}
	}
	return (1);
}

void    free_node(char *key, char *value, t_envi *env)
{
	free(key);
	free(value);
	free(env);
}

void    unset_node(char *key, t_envi **envi)
{
	t_envi 	*env;
	t_envi 	*del_node;
	t_envi 	*prec;

	env = *envi;
	if (env && !ft_strcmp(key, env->key))
	{
		del_node = env;
		*envi = env->next;
		del_node->next = NULL;
		free_node(del_node->key, del_node->value, del_node);
		return ;
	}
	while (env)
	{
		if (env->next &&!ft_strcmp(key, env->next->key))
		{
			prec = env;
			del_node = env->next;
			prec->next = del_node->next;
			del_node->next = NULL;
			free_node(del_node->key, del_node->value, del_node);
		}
		env = env->next;
	}
}

int    unset(char **av, t_envi **envi)
{
	int	i;
	int	exit_stat;

	i = -1;
	exit_stat = 0;
	while (envi && av[++i])
	{
		if (check_var(av[i], "unset", envi))
			unset_node(av[i], envi);
		else
			exit_stat = 1;
	}
	return (exit_stat);
}
