#include "../minishell.h"

void    unset(t_minishell *sh, char *var)
{
    t_env   *env;
    t_env   *prev;

    env = sh->env;
    if (ft_strrchr(var, '='))
        return ;
    while (env->next != NULL && ft_strncmp(env->next->var, var, ft_strlen(var)) != 0)
        env = env->next;
    prev = env;
    prev->next = env->next;
    env->next = NULL;
}
