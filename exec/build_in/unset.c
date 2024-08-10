#include "../../minishell.h"

void    unset(t_env **envi, char *var)
{
    t_env   *prev;
    t_env   *env;
    t_env   *rem_node;

    env = *envi;
    if (ft_strrchr(var, '='))
        return ;
    while (env->next != NULL && ft_strncmp(env->next->var, var, ft_strlen(var)) != 0)
        env = env->next;
    if (!env->next)
        return ;
    prev = env;
    rem_node = env->next;
    prev->next = rem_node->next;
    rem_node->next = NULL;
    *envi = env;
}
